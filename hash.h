#include <cstdlib>
#include <openssl/evp.h>
#include <string>

#define OPENSSL_ENGINE NULL

const std::string sha256( const std::string & input ) {
	EVP_MD_CTX *mdCtx = EVP_MD_CTX_new();
	if ( !EVP_DigestInit_ex( mdCtx, EVP_sha256(), OPENSSL_ENGINE ) ) {
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

	std::string mdVal;
	int mdLen;

	if ( !EVP_DigestFinal_ex( mdCtx, mdVal.c_str(), &mdLen ) ) {
		std::cerr << "Message digest finalizaion failed" << std::endl;
		EVP_MD_CTX_free( mdCtx );
		exit( EXIT_FAILURE );
	}

	EVP_MD_CTX_free( mdCtx );

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

