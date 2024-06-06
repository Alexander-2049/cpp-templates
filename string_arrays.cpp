#include <iostream>
#define MAX_STRING_SIZE 64

int main() {
	char character = 'a';
	std::cout << character << std::endl;

	char* pointerToCharacter = &character;
	std::cout << *pointerToCharacter << std::endl;

	char& referenceOfCharacter = character;
	std::cout << referenceOfCharacter << std::endl;

	// Defines an array with a copy of the string literal.
	// The characters in the array can be modified, but the array size is fixed.
	char characterArray[] = "character_array -> Hello, World!";
	std::cout << characterArray << std::endl;
	// ALLOWED:
	// character_array[0] = 'A';

	// Points to a string literal in read-only memory.
	// The pointer can be reassigned, but the string it points to should not be modified.
	const char* anotherCharacterArray = "another_character_array -> Hi!";
	std::cout << anotherCharacterArray << std::endl;
	// NOT ALLOWED:
	// another_character_array[0] = 'A';

	const int stringCount = 5;
	// Allocates memory for ${stringCount} pointers to C strings
	char** cStrings = (char**)malloc(stringCount * sizeof(char*));

	// In case of unsuccessfuly memory allocation end program execution
	if (cStrings == nullptr) {
		std::cerr << "Failed to allocate memory for cStrings." << std::endl;
		return 1;
	}

	// Allocate memory for C strings
	for (int i = 0; i < stringCount; i++) {
		// Allocate memory for a string of up to ${MAX_STRING_SIZE} characters plus null terminator
		char* p = (char*)malloc(MAX_STRING_SIZE + 1);
		// malloc(10) == malloc(10 * sizeof(char)); (equal as 'char' type takes 1 byte of memory)
		
		if (p != nullptr) {
			std::cout << "[DEBUG] cStrings[" << i << "] was allocated at " << static_cast<void*>(p) << std::endl;
			cStrings[i] = p; // Put C-string pointer in cStrings[i]
		}
		else {
			std::cerr << "Failed to allocate memory for string " << i << std::endl;
			for (int j = 0; j < i; j++) {
				// Frees memory that was allocated before failure
				free(cStrings[j]);
			}
			// Frees allocated memory for array of pointers
			free(cStrings);
			return 1;
		}
	}

	// Dynamically create ${stringCount} C++ strings
	std::string* strings = new std::string[stringCount];
	for (int i = 0; i < stringCount; i++)
	{
		// Simply make copy of C string
		// without loops
		strings[i] = cStrings[i];
	}

	/* ======== FREE ALLOCATED MEMORY ======== */
	for (int i = 0; i < stringCount; i++)
		free(cStrings[i]);
	free(cStrings);
	delete[] strings; // Deallocate C++ strings

	return 0;
}
