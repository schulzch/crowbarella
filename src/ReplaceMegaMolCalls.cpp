#include "Commands.h"
#include "clang/ASTMatchers/ASTMatchers.h"

#include <iostream>

using namespace clang;
using namespace clang::ast_matchers;
using namespace llvm;

class FixCall : public ast_matchers::MatchFinder::MatchCallback {
public:
  using ReplacementsType = std::map<std::string, clang::tooling::Replacements>;

  FixCall(ReplacementsType *Replacements) : Replacements(Replacements) {}

  void run(const ast_matchers::MatchFinder::MatchResult &Result) {
    const auto *C = Result.Nodes.getNodeAs<CXXOperatorCallExpr>("C");
    assert(C && "Resolving node failed");

    C->getCallee()->dump();
    std::cout << "---" << std::endl;
    C->dump();
    std::cout << "------" << std::endl;

    // Replaces->insert(Replacement(*Result.SourceManager, Call, ArgText));
  }

private:
  ReplacementsType *Replacements;
};

int replaceMegaMolCalls(
    clang::tooling::RefactoringTool &Tool,
    std::function<int(clang::ast_matchers::MatchFinder *)> RunFinder) {
  FixCall Callback(&Tool.getReplacements());
  ast_matchers::MatchFinder Finder;
  Finder.addMatcher(
      cxxOperatorCallExpr(hasOverloadedOperatorName("()")
                          //  declRefExpr(hasType(asString("class Call"))))
                          //  cxxRecordDecl(hasName("Call"))
                          )
          .bind("C"),
      &Callback);

  return RunFinder(&Finder);
}
