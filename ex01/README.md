# reinterpret_cast<uintptr_t>(&ptr) vs reinterpret_cast<uintptr_t>(ptr)

## reinterpret_cast<uintptr_t>(&ptr)
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




## reinterpret_cast<uintptr_t>(ptr)
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
