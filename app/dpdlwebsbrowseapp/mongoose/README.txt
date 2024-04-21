
This folder is supposed to contain the source code of the Mongoose C network Library 

https://github.com/cesanta/mongoose

Just two very small changes have been applied by SEE Solutions to the library source base, to provide better integration on the Dpdl platform.

The changes applied are reflected in the patch provided 'DpdlWebsBrowseApp_mongoose.patch'

Howto apply:

Copy the contents of the ./src folder found in the mongoose repository https://github.com/cesanta/mongoose
into the local ./src folder, and also in a new folder ./src_mod.
- Apply the patch
- delete the ./src folder
- rename the ./src_mod folder to ./src


