Output  :
    kernel m
    input m
    output m


-> the output m is the same size as input m 
-> inside convolution func  :
      - we flip the kernel m
      - we surrounder the input m with 0s to make output m same size 
      - we perform conv_calc
      - return the pointer of pointers of output m