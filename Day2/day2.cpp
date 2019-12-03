#include <cstddef>
#include <string>
#include <vector>
#include <sstream>
#include <optional>
#include <stdexcept>

enum class Opcode {
    ADD = 1,
    MULTIPLY = 2,
    HALT = 99
};

struct Operation {

    Opcode opcode;
    std::size_t x;
    std::size_t y;
    std::size_t output;

    Operation(Opcode opcode, std::size_t x, std::size_t y, std::size_t output) :
        opcode(opcode), x(x), y(y), output(output) {}

};

struct Executor {

    std::size_t instruction_pointer;
    std::vector<std::size_t> values;
    bool finished_execution;

    template<typename Container>
    Executor(Container&& values) :
        instruction_pointer(0), values(std::forward<Container>(values)), finished_execution(false) {}

        // According to the instructions we need to replace position#1 with the value
    void initialize(int noun, int verb) {
        // of noun and position#2 with the value of verb before running the program.
        this->values[1] = noun;
        this->values[2] = verb;
    }

    std::optional<Operation> get_next_operation() {
        if (finished_execution || values.size() - 1 < instruction_pointer) {
            return std::nullopt;
        }

        Opcode opcode = static_cast<Opcode>(values[instruction_pointer]);
        // Halt has no x, y and output to treat is specially
        if (opcode == Opcode::HALT) {
            return std::make_optional<Operation>(opcode, 0, 0, 0);
        }
        // Check if necessary operands are present
        if (values.size() < instruction_pointer + 4) {
            throw std::runtime_error("Missing operands for operation at '" + std::to_string(instruction_pointer) + "'.");
        }

        std::size_t x = values[instruction_pointer + 1];
        std::size_t y = values[instruction_pointer + 2];
        std::size_t output = values[instruction_pointer + 3];
        instruction_pointer += 4;
        return std::make_optional<Operation>(opcode, x, y, output);
    }

    void execute_operation(const Operation& operation) {
        switch (operation.opcode) {
        case Opcode::ADD:
            values[operation.output] = values[operation.x] + values[operation.y];
            break;
        case Opcode::MULTIPLY:
            values[operation.output] = values[operation.x] * values[operation.y];
            break;
        case Opcode::HALT:
            finished_execution = true;
            break;
        default:
            throw std::runtime_error("Unknown opcode '" +
                std::to_string(static_cast<int>(operation.opcode)) +
                "' at position '" +
                std::to_string(instruction_pointer) + "'.");
        }
    }

    void run_program() {
        std::optional<Operation> operation;
        while (operation = get_next_operation()) {
            execute_operation(*operation);
        }
    }

    std::size_t get_output() {
        if (!finished_execution) {
            throw std::runtime_error("Querying output before execution finished.");
        }
        return values[0];
    }

};

// This could be way more efficient using string_views but for this simple program we do not care.
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::string entry;
    std::vector<std::string> entries;
    std::stringstream input_stream(str);
    while (std::getline(input_stream, entry, delimiter)) {
        entries.emplace_back(std::move(entry));
    }
    return entries;
}
