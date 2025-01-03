#pragma once

#include <cstdlib>
#include <openssl/evp.h>
#include <iostream>
#include <string>

#define OPENSSL_ENGINE NULL

const std::string sha256( const std::string & input ) {
	EVP_MD_CTX *mdCtx = EVP_MD_CTX_new();
	const EVP_MD *md = EVP_sha256();
	if ( !EVP_DigestInit_ex( mdCtx, md, OPENSSL_ENGINE ) ) {
		std::cerr << "Message digest initialization failed" << std::endl;
		EVP_MD_CTX_free( mdCtx );
		exit( EXIT_FAILURE );
	}

	// Hashes cnt bytes of data at d into the digest context mdCtx
	if ( !EVP_DigestUpdate( mdCtx, input.c_str(), input.size() ) ) {
		std::cerr << "Message digest update failed" << std::endl;
		EVP_MD_CTX_free( mdCtx );
		exit( EXIT_FAILURE );
	}

	unsigned int mdLen = EVP_MD_size( md );
	std::string mdVal( mdLen, '\0' );

	if ( !EVP_DigestFinal_ex( mdCtx, reinterpret_cast< unsigned char * >( &mdVal[ 0 ] ), &mdLen ) ) {
		std::cerr << "Message digest finalizaion failed" << std::endl;
		EVP_MD_CTX_free( mdCtx );
		exit( EXIT_FAILURE );
	}

	EVP_MD_CTX_free( mdCtx );

	mdVal.resize( mdLen );

	return mdVal;
}

// TODO: Avoid extra string copies and allocations
int hash( int x, int y, int z ) {
	std::string hashInput = std::to_string( x ) + "-" + std::to_string( y ) + "-" +
				std::to_string( z );
	std::string hashValue = sha256( hashInput );
	std::string hexHashValue = "0x" + hashValue;
	return std::stoul( hexHashValue, nullptr, 16 );
}

