#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <set>
#include <map>
#include <functional>
#include <numeric>

enum class Op
{
  addr,
  addi,
  mulr,
  muli,
  banr,
  bani,
  borr,
  bori,
  setr,
  seti,
  gtir,
  gtri,
  gtrr,
  eqir,
  eqri,
  eqrr
};

struct Instruction
{
  Op op;
  std::array<int64_t, 3> data;
};

Op to_Op(const std::string &op_name)
{
  std::vector<std::string> op_names(
    {"addr", "addi", "mulr", "muli", "banr", "bani", "borr", "bori", "setr",
     "seti", "gtir", "gtri", "gtrr", "eqir", "eqri", "eqrr"});

  auto op(std::find(op_names.begin(), op_names.end(), op_name));
  if(op == op_names.end())
    abort();
  return static_cast<Op>(std::distance(op_names.begin(), op));
}

std::istream &operator>>(std::istream &is, Instruction &instruction)
{
  std::string op_name;
  is >> op_name;
  if(is.good())
    {
      instruction.op = to_Op(op_name);
      is >> instruction.data[0] >> instruction.data[1] >> instruction.data[2];
    }
  return is;
}

std::ostream &operator<<(std::ostream &os, const Instruction &instruction)
{
  std::vector<std::string> op_names(
    {"addr", "addi", "mulr", "muli", "banr", "bani", "borr", "bori", "setr",
     "seti", "gtir", "gtri", "gtrr", "eqir", "eqri", "eqrr"});
  os << op_names[static_cast<int64_t>(instruction.op)] << " "
     << instruction.data[0] << " " << instruction.data[1] << " "
     << instruction.data[2];

  return os;
}

void
  apply_op(std::array<int64_t, 6> &registers, const Instruction &instruction)
{
  auto &input(instruction.data);

  switch(instruction.op)
    {
    case Op::addr:
      registers[input[2]] = registers[input[0]] + registers[input[1]];
      break;
    case Op::addi: registers[input[2]] = registers[input[0]] + input[1]; break;
    case Op::mulr:
      registers[input[2]] = registers[input[0]] * registers[input[1]];
      break;
    case Op::muli: registers[input[2]] = registers[input[0]] * input[1]; break;
    case Op::banr:
      registers[input[2]] = registers[input[0]] & registers[input[1]];
      break;
    case Op::bani: registers[input[2]] = registers[input[0]] & input[1]; break;
    case Op::borr:
      registers[input[2]] = registers[input[0]] | registers[input[1]];
      break;
    case Op::bori: registers[input[2]] = registers[input[0]] | input[1]; break;
    case Op::setr: registers[input[2]] = registers[input[0]]; break;
    case Op::seti: registers[input[2]] = input[0]; break;
    case Op::gtir:
      registers[input[2]] = (input[0] > registers[input[1]] ? 1 : 0);
      break;
    case Op::gtri:
      registers[input[2]] = (registers[input[0]] > input[1] ? 1 : 0);
      break;
    case Op::gtrr:
      registers[input[2]]
        = (registers[input[0]] > registers[input[1]] ? 1 : 0);
      break;
    case Op::eqir:
      registers[input[2]] = (input[0] == registers[input[1]] ? 1 : 0);
      break;
    case Op::eqri:
      registers[input[2]] = (registers[input[0]] == input[1] ? 1 : 0);
      break;
    case Op::eqrr:
      registers[input[2]]
        = (registers[input[0]] == registers[input[1]] ? 1 : 0);
      break;
    }
}

int main(int, char *argv[])
{
  std::ifstream infile("input.txt");
  std::string temp;
  int64_t ip;
  infile >> temp >> ip;
  std::vector<Instruction> instructions(
    std::istream_iterator<Instruction>(infile), {});

  std::set<int64_t> stopping_values;
  int64_t last_stop;

  std::array<int64_t, 6> registers;
  registers.fill(0);

while(true)
  {
    apply_op(registers, instructions[registers[ip]]);
    ++registers[ip];
    if(registers[ip] == 28)
      {
        if(stopping_values.find(registers[2]) == stopping_values.end())
          {
            if(stopping_values.empty())
              {
                std::cout << "Part 1: " << registers[2] << "\n";
              }
            stopping_values.insert(registers[2]);
            last_stop = registers[2];
            std::cout << "adding stopping value " << last_stop << "\n";
          }
        else
          {
            break;
          }
      }
  }
std::cout << "Part 2: " << last_stop << "\n";
}