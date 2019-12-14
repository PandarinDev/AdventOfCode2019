#include <cstddef>
#include <string>
#include <vector>
#include <array>
#include <sstream>
#include <optional>
#include <stdexcept>
#include <functional>

// Left pads a string with the supplied padding character to the minimum width
std::string string_left_pad(std::string str, std::size_t min_width, char pad_char) {
    while (str.size() < min_width) {
        str = pad_char + str;
    }
    return str;
}

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

enum class Opcode {
    ADD = 1,
    MULTIPLY = 2,
    SAVE_INPUT = 3,
    OUTPUT_VALUE = 4,
    HALT = 99
};

std::int8_t get_number_of_parameters_for_opcode(Opcode opcode) {
    switch (opcode) {
    case Opcode::ADD:
    case Opcode::MULTIPLY:
        return 3;
    case Opcode::SAVE_INPUT:
    case Opcode::OUTPUT_VALUE:
        return 1;
    case Opcode::HALT:
        return 0;
    }
    throw std::runtime_error("Unknown opcode passed to function.");
}

enum class ParameterMode {
    POSITION_MODE = '0',
    IMMEDIATE_MODE = '1'
};

struct Parameter {

    std::size_t value;
    ParameterMode mode;

    Parameter() : value(0), mode(ParameterMode::POSITION_MODE) {}

    Parameter(std::size_t value, ParameterMode mode) :
        value(value), mode(mode) {}

};

struct Operation {

    Opcode opcode;
    std::vector<Parameter> parameters;

    Operation(
        Opcode opcode,
        const std::vector<Parameter>& parameters) :
        opcode(opcode), parameters(parameters) {}

};

struct Executor {

    using InputSupplier = std::function<std::size_t()>;
    using OutputConsumer = std::function<void(std::size_t, const std::optional<Operation>&)>;

    std::size_t instruction_pointer;
    std::vector<std::size_t> values;
    InputSupplier input_supplier;
    OutputConsumer output_consumer;
    bool finished_execution;

    template<typename Container>
    Executor(
        Container&& values,
        const InputSupplier& input_supplier,
        const OutputConsumer& output_consumer) :
        instruction_pointer(0),
        values(std::forward<Container>(values)),
        input_supplier(input_supplier),
        output_consumer(output_consumer),
        finished_execution(false) {}

    // According to the instructions we need to replace position#1 with the value
    // of noun and position#2 with the value of verb before running the program.
    void initialize(std::size_t noun, std::size_t verb) {
        this->values[1] = noun;
        this->values[2] = verb;
    }

    std::optional<Operation> get_next_operation() {
        if (finished_execution || values.size() - 1 < instruction_pointer) {
            return std::nullopt;
        }
    
        std::string opcode_str = string_left_pad(std::to_string(values[instruction_pointer]), 5, '0');
        std::array<ParameterMode, 3> parameter_modes {
            static_cast<ParameterMode>(opcode_str[2]),
            static_cast<ParameterMode>(opcode_str[1]),
            static_cast<ParameterMode>(opcode_str[0])
        };
        Opcode opcode = static_cast<Opcode>(std::stoi(opcode_str.substr(opcode_str.size() - 2)));
        auto number_of_parameters = get_number_of_parameters_for_opcode(opcode);
        std::vector<Parameter> parameters(number_of_parameters);
        // Check if necessary operands are present
        if (values.size() < instruction_pointer + number_of_parameters) {
            throw std::runtime_error("Missing operands for operation at '" + std::to_string(instruction_pointer) + "'.");
        }
        // Collect the parameters
        for (std::int8_t i = 0; i < number_of_parameters; ++i) {
            parameters[i] = Parameter(values[instruction_pointer + i + 1], parameter_modes[i]);
        }

        instruction_pointer += number_of_parameters + 1;
        return std::make_optional<Operation>(opcode, parameters);
    }

    void execute_operation(const Operation& operation, const std::optional<Operation>& next_operation) {
        // Collect parameter values
        std::vector<std::size_t> parameter_values(operation.parameters.size());
        for (std::int8_t i = 0; i < parameter_values.size(); ++i) {
            const auto& parameter = operation.parameters[i];
            switch (parameter.mode) {
            case ParameterMode::POSITION_MODE:
                parameter_values[i] = values[parameter.value];
                break;
            case ParameterMode::IMMEDIATE_MODE:
                parameter_values[i] = parameter.value;
                break;
            default: throw std::runtime_error("Unknown parameter mode in function.");
            }
        }

        switch (operation.opcode) {
        case Opcode::ADD:
            values[parameter_values[2]] = values[parameter_values[0]] + values[parameter_values[1]];
            break;
        case Opcode::MULTIPLY:
            values[parameter_values[2]] = values[parameter_values[0]] * values[parameter_values[1]];
            break;
        case Opcode::SAVE_INPUT:
            values[parameter_values[0]] = input_supplier();
            break;
        case Opcode::OUTPUT_VALUE:
            output_consumer(parameter_values[0], next_operation);
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
        std::vector<Operation> operations;
        while (operation = get_next_operation()) {
            operations.emplace_back(*operation);
        }

        for (std::size_t i = 0; i < operations.size(); ++i) {
            const auto& operation = operations[i];
            std::optional<Operation> next_operation = (i < operations.size() - 1)
                ? std::make_optional<Operation>(operations[i + 1])
                : std::nullopt;
            execute_operation(operation, next_operation);
        }
    }

    std::size_t get_output() {
        if (!finished_execution) {
            throw std::runtime_error("Querying output before execution finished.");
        }
        return values[0];
    }

};
