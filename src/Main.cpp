#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CompilationDatabase.h"
#include "clang/Tooling/Refactoring.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/ADT/Twine.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Signals.h"

#include "Commands.h"
#include <memory>

using namespace clang;
using namespace llvm;

cl::opt<std::string> BuildPath(cl::Positional, cl::desc("<build-path>"));

cl::list<std::string> SourcePaths(cl::Positional,
                                  cl::desc("<source0> [... <sourceN>]"),
                                  cl::OneOrMore);

cl::opt<bool> Dry("d", cl::desc("Dry run"));

int main(int argc, const char **argv) {
  sys::PrintStackTraceOnErrorSignal(argv[0]);
  std::string ErrorMessage;
  std::unique_ptr<tooling::CompilationDatabase> Compilations(
      tooling::FixedCompilationDatabase::loadFromCommandLine(argc, argv,
                                                             ErrorMessage));
  cl::ParseCommandLineOptions(argc, argv);
  if (!Compilations) {
    Compilations = tooling::CompilationDatabase::loadFromDirectory(
        BuildPath, ErrorMessage);
    if (!Compilations)
      report_fatal_error(ErrorMessage);
  }
  tooling::RefactoringTool Tool(*Compilations, SourcePaths);

  std::unique_ptr<tooling::FrontendActionFactory> Factory;

  Factory.reset(createReplaceClass(Tool));

  assert(!Factory && "Action was not properly created!");

  if (Dry) {
    return Tool.run(Factory.get());
  } else {
    return Tool.runAndSave(Factory.get());
  }
}
