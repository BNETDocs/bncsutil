/*
 * BNCSutil
 * Copyright (c) 2004-2006 Eric Naeseth.
 *
 * NLS C++ Binding Test
 * April 1, 2006
 */

#include <bncsutil/bncsutil.h>

int main()
{
	char salt[32];
	char B[32];
	int i;
	int j = 0;

	for (i = 0; i < 32; i++) {
		salt[i] = j++;
	}
	for (i = 0; i < 32; i++) {
		B[i] = j++;
	}

	NLS nls("Cloaked", "foo");
	bncsutil_debug_message("NLS Test");
	bncsutil_debug_message("Salt:");
	bncsutil_debug_dump(salt, 32);
	bncsutil_debug_message("Client public key:");
	bncsutil_debug_dump(nls.getPublicKey(), 32);
	bncsutil_debug_message("Server public key:");
	bncsutil_debug_dump(B, 32);
	bncsutil_debug_message("Client session key:");
	bncsutil_debug_dump(nls.getClientSessionKey(salt, B), 20);
	return 0;
}