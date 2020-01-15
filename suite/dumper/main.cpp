#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "ast/query.hpp"
#include "diagnostics/controller.hpp"
#include "parser/parser.hpp"
#include "writer/directory.hpp"

using namespace std;

void dumpTypes(AST::Program* program) {
  std::vector<std::string> types = program->getTypeNames();
  std::sort(types.begin(), types.end());

  std::cout << "---TYPES---" << std::endl;
  for (int i = 0; i < types.size(); ++i) {
    Type::Object* type = program->getType(types[i]);
    std::vector<Type::Object*> bases = type->getBases();
    std::vector<std::string> fields = type->getOwnedFields();

    std::cout << "---" << type->getName() << "---" << std::endl;
    for (int j = 0; j < bases.size(); ++j)
      std::cout << "BASE " << bases[j]->getName() << std::endl;
    for (int j = 0; j < fields.size(); ++j) {
      std::cout << "OWN ";
      if (type->isNullable(fields[j]))
        std::cout << "NULLABLE ";
      std::cout << fields[j];
      std::cout << " TYPE " << type->query(fields[j])->toString() << std::endl;
    }
    std::cout << "/--" << type->getName() << "---" << std::endl;
    if (i + 1 != types.size())
      std::cout << std::endl;
  }
  std::cout << "/--TYPES---" << std::endl;
}

void dumpQuery(AST::Query* query) {
  std::vector<AST::PipelineInfo> pipelines = query->getPipelines();
  for (int i = 0; i < pipelines.size(); ++i) {
    AST::PipelineInfo pipeline = pipelines[i];
    std::cout << "TYPE " << pipeline.inputType->toString() << std::endl;
    std::cout << "-->" << pipeline.call->getCalleeName() << std::endl;
    std::vector<Value::Container*> arguments = pipeline.call->getArguments();
    for (int j = 0; j < arguments.size(); ++j) {
      if (arguments[j]->isQuery()) {
        std::cout << "---SUB-QUERY---" << std::endl;
        dumpQuery(arguments[j]->asQuery());
        std::cout << "/--SUB-QUERY---" << std::endl;
      }
    }
  }
  std::cout << "RESULT " << query->getResultType()->toString() << std::endl;
}

void dumpPermissions(AST::Program* program) {
  std::vector<std::string> names = program->getPermissionNames();
  std::sort(names.begin(), names.end());

  std::cout << "---PERMISSIONS---" << std::endl;
  for (int i = 0; i < names.size(); ++i) {
    AST::Permission* permission = program->getPermission(names[i]);
    std::cout << "---" << permission->getName() << "---" << std::endl;
    dumpQuery(permission->getQuery());
    std::cout << "/--" << permission->getName() << "---" << std::endl;
    if (i + 1 != names.size())
      std::cout << std::endl;
  }
  std::cout << "/--PERMISSIONS---" << std::endl;
}

void dumpQueries(AST::Program* program) {
  std::vector<std::string> names = program->getQueryNames();
  std::sort(names.begin(), names.end());

  std::cout << "---QUERIES---" << std::endl;
  for (int i = 0; i < names.size(); ++i) {
    AST::Query* query = program->getQuery(names[i]);
    Type::Container* userType =
        query->getParameterType(query->getParameterId("%user"));
    std::cout << "---" << names[i] << "---" << std::endl;
    std::cout << "USER " << userType->toString() << std::endl;
    dumpQuery(query);
    std::cout << "/--" << names[i] << "---" << std::endl;
    if (i + 1 != names.size())
      std::cout << std::endl;
  }
  std::cout << "/--QUERIES---" << std::endl;
}

void dump(AST::Program* program) {
  dumpTypes(program);
  std::cout << std::endl;
  dumpPermissions(program);
  std::cout << std::endl;
  dumpQueries(program);
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <filename>" << endl;
    return -1;
  }

  std::ifstream t(argv[1]);

  if (!t.is_open()) {
    cerr << "There was an error trying to read " << argv[1] << endl;
    return -1;
  }

  std::stringstream buffer;
  buffer << t.rdbuf();

  AST::Program* program = Parser::createProgram(buffer.str());

  if (Diagnostics::Controller::hasError()) {
    Diagnostics::Controller::dumpAll();
    return -1;
  }

  dump(program);
  return 0;
}