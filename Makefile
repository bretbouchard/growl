# Makefile for Growl DSP Test
# Standalone test without requiring full JUCE installation

CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2
INCLUDES = -Iinclude
LDFLAGS = -framework Accelerate

# Targets
all: test

test: tests/GrowlDSPTest.cpp
	@echo "Building Growl DSP Test..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) tests/GrowlDSPTest.cpp $(LDFLAGS) -o build/growl_test
	@echo "Running DSP Test..."
	@./build/growl_test

clean:
	@echo "Cleaning build artifacts..."
	@rm -rf build/
	@echo "✓ Clean complete"

help:
	@echo "Available targets:"
	@echo "  make test      - Build and run DSP test"
	@echo "  make clean     - Clean build artifacts"
	@echo "  make help      - Show this help message"

.PHONY: all test clean help
