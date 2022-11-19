# multi


---

# Purpose
## Extracts the UO multi entries in multi.idx/mul or MultiCollecton.uop to individual text files that can be edited.
## Alternatively it can create a multi.idx/mul or MultiColleciton.uop from the text entries in a directory
<details>
Usage:

  multi flag csvdirectory uopfile
  where:
  flag is --create or --extract
  
or

  multi flag csvdirectory idxfile mulfile
  flag is --create or --extract

# Using multi for converting
## multi can be used to convert from uop to idx/mul or vice versa
<details>
  To do so, first extract from an uop (this will get a housing.bin file)
  
  multi --extract uop MultiCollection.uop  << this will create entries in a subdirectory uop
  multi --extract mul multi.idx multi.mul << this will create entries in a subdirectory mul
  
  Now, edit the entries in the uop directory to match the ones you want in the mul directory.
  Note:  uop entires have a cliloc field in the csv directory, which the mul ones are blank.
  You may wish to keep that entry, thus edit the csv versus overwriting.
  
  Now, to create the files
  
  multi --create uop MultiColleciton.uop  << this will create a new file.
  
  