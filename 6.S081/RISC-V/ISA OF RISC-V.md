## ISA OF RISC-V

### Basic instructions

```assembly
# la: load address. It is as same as `lea` in x86. Note that it loads the value of 
# "stack0" to "sp". The source and destination operands are opposite from x86.
la sp, stack0

# li: load immediate
li a0, 1024*4
```

