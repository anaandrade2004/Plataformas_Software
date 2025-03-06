from collections import Counter

# Function to count characters in a text file
def count_characters_in_file(file_path):
    try:
        # Open the file in read mode
        with open(file_path, 'r') as file:
            # Read the content of the file
            text = file.read()
            
            # Count the occurrences of each character using Counter
            character_count = Counter(text)
            
            # Return the character count
            return character_count
            
    except FileNotFoundError:
        print(f"Error: The file at '{file_path}' was not found.")
        return None

# Example usage
file_path = 'dna_100.txt'  # Replace with your file path
character_count = count_characters_in_file(file_path)

if character_count:
    print("Character count in the file:")
    for char, count in character_count.items():
        print(f"'{char}': {count}")

