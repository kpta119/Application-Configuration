# Configuration System

## Project Description
This project implements a **key-value configuration system** that allows managing application settings.  
The configuration stores string values indexed by string keys and supports read-only mode.

### Key Features:
- **Modifiable Configuration**: New entries can be added until the configuration is set to read-only.
- **Read-Only Mode**: Once `setWriteProtection()` is called, the configuration cannot be modified.
- **Mathematical Operators**:
  - `+`, `+=` → Merges two configurations (left operand has priority for duplicate keys).
  - `-`, `-=` → Removes keys present in the right operand from the left operand.
- **Additional Operations**:
  - `write(key, value)`: Adds a key-value pair and returns `true` if successful.
  - `operator[]`: Provides read-only access to values.
  - `hasKey(key)`: Checks if a key exists.

## Project Structure
- `ConfigurationLib/` – Source code files with implementation of configuration
- `ConfigurationTest/` – Unit tests
- `README.md` – Project documentation

## Implementation Details
- **Encapsulation**: Proper use of `public` and `private` members.
- **Immutability Control**: Ensures that a read-only configuration cannot be modified.
- **Stream Operators**: Supports `<<` for outputting the configuration.
- **Unit Tests**: Verifies correctness of key functionalities.


