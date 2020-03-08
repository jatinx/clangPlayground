#include <clang/Tooling/Tooling.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace clang;
constexpr auto fact{R"(
int fac(int f) { return (f < 2) ? f : f * fac(f - 1); }
)"};

int main() {
  std::unique_ptr<ASTUnit> AST(tooling::buildASTFromCode(fact));
  TranslationUnitDecl *DC = AST->getASTContext().getTranslationUnitDecl();
  if (DC) {
    llvm::errs() << "---------dump begin----------\n";
    DC->dump();
    llvm::errs() << "---------dump end----------\n";
  }
}
