# file: crypt/crypt.sh

# ====================================================================
# files;
# --------------------------------------------------------------------

b64write.o: b64write.c format.h base64.h types.h
SHA256.o: SHA256.c SHA256Reset.c SHA256Write.c SHA256Block.c SHA256Fetch.c SHA256.h 
SHA256Block.o: SHA256Block.c SHA256.h 
SHA256Fetch.o: SHA256Fetch.c SHA256.h 
SHA256Reset.o: SHA256Reset.c SHA256.h 
SHA256Write.o: SHA256Write.c SHA256.h 
SHA256Print.o: SHA256Print.c SHA256.h number.h 
SHA256Match.o: SHA256Match.c SHA256.h number.h 
SHA256Ident.o: SHA256Ident.c SHA256.h
MD5Reset.o: MD5Reset.c MD5.h
MD5Write.o: MD5Write.c MD5.h
MD5Block.o: MD5Block.c MD5.h
MD5Fetch.o: MD5Fetch.c MD5.h
MD5Fetch.o: MD5Print.c MD5.h number.h

# ====================================================================
# files;
# --------------------------------------------------------------------

SHA256.h: types.h
	touch ../crypt/${@}

