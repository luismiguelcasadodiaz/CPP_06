#234567890123456789012345678901234567890123456789012345678901234567890123456789#
#        1         2         3         4         5         6         7         #
#..............................................................................#
# Luis Miguel Casado Díaz (LMCD) .gdbinit configuration file                   #
#                                                                              #
# 2024_06_09                                                                   #
#..............................................................................#

# To enable execution of this file, ensure you have a inside file
# ~/.config/gdb/gdbinit
# a line starting with add-auto-load-safe-path <absolute path to this file>
# add-auto-load-safe-path /home/......../circle4/namada_minshell/.gdbinit
# to enable history of gdb cli
set history save on
# to remove duplicates form history
set history remove-duplicates 1
# to enable Debuginfo
#set debuginfo enabled on
# To print structs in a more readable form
set print pretty on
# Follow child at fork()
set follow-fork-mode child
# To keep father & child under control with "inferior" command
set detach-on-fork off

# Set Breakpoint at main function
#break main:

#break a la entrade de una función
#break eleme_hittables_sph.c:hit_sphere 

# Set other breakpoint
#break init.c:108
#break init.c:117
#break win_init.c:75

#Break condicional
#break is_scene4.c:73  if ((wy0 == 140) && (wx0 ==250))

######################  Breaks FT_IRC  ######################################


#break ScalarConverter.cpp:41
break main
display &lmcd
display lmcd
display *lmcd
display &dser
display dser
display *dser
run 
