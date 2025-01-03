#pragma once

#include <cassert>
#include <cmath>

#include "hash.h"

// Check if n is a prime
bool
isPrime( int n ) {
	double sqrtN = sqrt( n );
	for ( int i = 2; i <= sqrtN; ++i ) {
		if ( n % i == 0 ) {
			return false;
		}
	}
	return true;
}

// Return the smallest prime number p >= n
// TODO: Use better algorithm
int
nextPrime( int n ) {
	for ( int i = n; i < 2 * n; ++i ) {
		if ( isPrime( i ) ) {
			return i;
		}
	}
	assert( 0 && "Could not find a prime number" );
	// Satisfy the compiler
	return -1;
}

// Select the smallest prime number p >= a
int
selectPrime( int a, int b, int c ) {
	int hashValue = hash( b, c, 1 );
	int candidate = std::max( a, hashValue % ( 2 * a ) );
	return nextPrime( candidate );
}
