# reinterpret_cast<uintptr_t>(&ptr) vs reinterpret_cast<uintptr_t>(ptr)

## reinterpret_cast<uintptr_t>(&ptr) ❌ 

lmcd is a variable of type pointer to Data.
lmcd variable is located at 0x7fffffffdd48 address
lmcd content is the the address 0x55555556aeb0
### after Initialization
```gdb
&lmcd = (Data **) 0x7fffffffdd48
lmcd = (Data *) 0x55555556aeb0
*lmcd = {
  nom = "Luis Miguel",
  ape = "Casado Diaz",
  age = 59
}
&dser = (Data **) 0x7fffffffdd58
dser = (Data *) 0x7ffff7fa1e88 <std::wclog+8>
*dser = {
  nom = "PG\353\367\377\177",
  ape = "",
  age = 0
}
```
### Inside Serialize
static uintptr_t serialize( Data * ptr) ;
raw = Serializer::serialize( lmcd ) ;

```gdb
Serializer::serialize (ptr=0x55555556aeb0) at Serializer.cpp:13
		return reinterpret_cast<uintptr_t>(&ptr);

```
serialize reinterprets lmcd address 0x55555556AEB0 (a memory address)
as an unsigned integer value 140737488346408

### Inside deserialize
dser = Serializer::deserialize( raw ) ;
```gdb
Serializer::deserialize (raw=140737488346408) at Serializer.cpp:16
		return reinterpret_cast<Data *>(raw) ;}
```
Deserialize converts 140737488346408 into 0x7FFFFFFFDD28

### After deserialize
```gdb
&lmcd = (Data **) 0x7fffffffdd48
lmcd = (Data *) 0x55555556aeb0
*lmcd = {
  nom = "Luis Miguel",
  ape = "Casado Diaz",
  age = 59
}
&dser = (Data **) 0x7fffffffdd58
dser = (Data *) 0x7fffffffdd28
*dser = {
  nom = "",
  ape = "",
  age = 140737488346760
}
```



## reinterpret_cast<uintptr_t>(ptr) ✅ 
### after Initialization
```gdb
&lmcd = (Data **) 0x7fffffffdd48
lmcd = (Data *) 0x55555556aeb0
*lmcd = {
  nom = "Luis Miguel",
  ape = "Casado Diaz",
  age = 59
}
&dser = (Data **) 0x7fffffffdd58
dser = (Data *) 0x7ffff7fa1e88 <std::wclog+8>
*dser = {
  nom = "PG\353\367\377\177",
  ape = "",
  age = 0
}
```

### Inside Serialize
static uintptr_t serialize( Data * ptr)
raw = Serializer::serialize( lmcd ) ;

```gdb
Serializer::serialize (ptr=0x55555556aeb0) at Serializer.cpp:13
		return reinterpret_cast<uintptr_t>(ptr);

```
serialize reinterprets lmcd pointer value 0x55555556AEB0 (a memory address)
as an unsigned integer value 93824992325296

### Inside deserialize
dser = Serializer::deserialize( raw ) ;
```gdb
Serializer::deserialize (raw=93824992325296) at Serializer.cpp:16
		return reinterpret_cast<Data *>(raw) ;}
```
Deserialize converts 93824992325296 into 0x55555556AEB0


### After deserialize
```gdb
&lmcd = (Data **) 0x7fffffffdd48
lmcd = (Data *) 0x55555556aeb0
*lmcd = {
  nom = "Luis Miguel",
  ape = "Casado Diaz",
  age = 59
}
&dser = (Data **) 0x7fffffffdd58
dser = (Data *) 0x55555556aeb0
*dser = {
  nom = "Luis Miguel",
  ape = "Casado Diaz",
  age = 59
}


### use bc to verify.
```bash
% bc
bc 1.07.1
Copyright 1991-1994, 1997, 1998, 2000, 2004, 2006, 2008, 2012-2017 Free Software Foundation, Inc.
This is free software with ABSOLUTELY NO WARRANTY.
For details type `warranty'. 
obase=16
93824992325296
55555556AEB0   // lmcd
140737488346408
7FFFFFFFDD28   // &lmcd

```

# Other use cases of reinterpret_cast

### Network Programming byte order Conversion
```c++
char buffer[4] = {0x12, 0x34, 0x56, 0x78};
// Interpret as 32-bit integer
uint32_t* value = reinterpret_cast<uint32_t*>(buffer);
std::cout << std::hex << *value << std::endl;  // 0x78563412 (little-endian)
```
Reinterpret the buffer address as an uint32_t pointer value, then use value content *value

### Reading raw bytes of any object
```c++
struct Data_ {
	int x;
	float y;
};

Data_ d = {42, 3.14f};

unsigned char* bytes = reinterpret_cast<unsigned char*>(&d);

// Simulate bytes travelling in the network as a stream
unsigned char received[sizeof(bytes)];
for (size_t i = 0; i < sizeof(Data_); i++) {
	received[i] = bytes[i];

Data_ * r = reinterpret_cast<Data_ *>(received) ;
}

```
Reinterpret d's address as a pointer to an unsigend char.
"send" such stream of bytes.
Reinterpret received stream of bytes as a pointer to Data_r

```c++
uint32_t bits = *reinterpret_cast<uint32_t *>(&d.y) ;

```
Reinterpret a float's address as a pointer to a uint32_t, then assign pointer's
content to an uint32_t `bits` var
# What i learnt
### Persitent outpout manipulators stick until changed

Persistent stream manipulators:

✅ std::hex, std::dec, std::oct (number base)

✅ std::fixed, std::scientific (float format)

✅ std::setprecision(n) (decimal places)

✅ std::setw(n) (field width) - EXCEPTION: only affects next item!

✅ std::setfill(c) (fill character)

✅ std::showpos, std::noshowpos (show + sign)

✅ std::uppercase, std::nouppercase (case for hex/scientific)


### reset all formating to default
std::cout.copyfmt(std::ios(NULL));  // Reset all formatting to defaults
