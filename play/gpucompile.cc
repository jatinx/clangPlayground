/* compile 
clang++ compile.cc -o main -L/usr/local/lib  -I/usr/local/include -std=c++14   -fno-exceptions -fno-rtti -D_GNU_SOURCE -D_DEBUG -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -I/home/jatin/github/llvm-project/clang/lib/CodeGen -lLLVMXRay -lLLVMWindowsManifest -lLLVMTableGen -lLLVMSymbolize -lLLVMDebugInfoPDB -lLLVMOrcJIT -lLLVMOrcError -lLLVMJITLink -lLLVMObjectYAML -lLLVMMCA -lLLVMLTO -lLLVMPasses -lLLVMCoroutines -lLLVMObjCARCOpts -lLLVMLineEditor -lLLVMLibDriver -lLLVMInterpreter -lLLVMFuzzMutate -lLLVMMCJIT -lLLVMExecutionEngine -lLLVMRuntimeDyld -lLLVMDWARFLinker -lLLVMDlltoolDriver -lLLVMOption -lLLVMDebugInfoGSYM -lLLVMCoverage -lLLVMXCoreDisassembler -lLLVMXCoreCodeGen -lLLVMXCoreDesc -lLLVMXCoreInfo -lLLVMX86Disassembler -lLLVMX86AsmParser -lLLVMX86CodeGen -lLLVMX86Desc -lLLVMX86Utils -lLLVMX86Info -lLLVMWebAssemblyDisassembler -lLLVMWebAssemblyCodeGen -lLLVMWebAssemblyDesc -lLLVMWebAssemblyAsmParser -lLLVMWebAssemblyInfo -lLLVMSystemZDisassembler -lLLVMSystemZCodeGen -lLLVMSystemZAsmParser -lLLVMSystemZDesc -lLLVMSystemZInfo -lLLVMSparcDisassembler -lLLVMSparcCodeGen -lLLVMSparcAsmParser -lLLVMSparcDesc -lLLVMSparcInfo -lLLVMRISCVDisassembler -lLLVMRISCVCodeGen -lLLVMRISCVAsmParser -lLLVMRISCVDesc -lLLVMRISCVUtils -lLLVMRISCVInfo -lLLVMPowerPCDisassembler -lLLVMPowerPCCodeGen -lLLVMPowerPCAsmParser -lLLVMPowerPCDesc -lLLVMPowerPCInfo -lLLVMNVPTXCodeGen -lLLVMNVPTXDesc -lLLVMNVPTXInfo -lLLVMMSP430Disassembler -lLLVMMSP430CodeGen -lLLVMMSP430AsmParser -lLLVMMSP430Desc -lLLVMMSP430Info -lLLVMMipsDisassembler -lLLVMMipsCodeGen -lLLVMMipsAsmParser -lLLVMMipsDesc -lLLVMMipsInfo -lLLVMLanaiDisassembler -lLLVMLanaiCodeGen -lLLVMLanaiAsmParser -lLLVMLanaiDesc -lLLVMLanaiInfo -lLLVMHexagonDisassembler -lLLVMHexagonCodeGen -lLLVMHexagonAsmParser -lLLVMHexagonDesc -lLLVMHexagonInfo -lLLVMBPFDisassembler -lLLVMBPFCodeGen -lLLVMBPFAsmParser -lLLVMBPFDesc -lLLVMBPFInfo -lLLVMARMDisassembler -lLLVMARMCodeGen -lLLVMARMAsmParser -lLLVMARMDesc -lLLVMARMUtils -lLLVMARMInfo -lLLVMAMDGPUDisassembler -lLLVMAMDGPUCodeGen -lLLVMMIRParser -lLLVMipo -lLLVMInstrumentation -lLLVMVectorize -lLLVMLinker -lLLVMIRReader -lLLVMAsmParser -lLLVMFrontendOpenMP -lLLVMAMDGPUAsmParser -lLLVMAMDGPUDesc -lLLVMAMDGPUUtils -lLLVMAMDGPUInfo -lLLVMAArch64Disassembler -lLLVMMCDisassembler -lLLVMAArch64CodeGen -lLLVMCFGuard -lLLVMGlobalISel -lLLVMSelectionDAG -lLLVMAsmPrinter -lLLVMDebugInfoDWARF -lLLVMCodeGen -lLLVMTarget -lLLVMScalarOpts -lLLVMInstCombine -lLLVMAggressiveInstCombine -lLLVMTransformUtils -lLLVMBitWriter -lLLVMAnalysis -lLLVMProfileData -lLLVMObject -lLLVMTextAPI -lLLVMBitReader -lLLVMCore -lLLVMRemarks -lLLVMBitstreamReader -lLLVMAArch64AsmParser -lLLVMMCParser -lLLVMAArch64Desc -lLLVMMC -lLLVMDebugInfoCodeView -lLLVMDebugInfoMSF -lLLVMBinaryFormat -lLLVMAArch64Utils -lLLVMAArch64Info -lLLVMSupport -lLLVMDemangle -lclang -lclangIndex -lclangFrontend -lclangDriver -lclangSerialization -lclangParse -lclangSema -lclangAnalysis -lclangAST -lclangLex -lclangBasic -ldl -lpthread -ltinfo -lLLVMSupport -lz -lLLVMMC -lLLVMMCA -lclangTooling -lclangEdit -lclangCodeGen -fuse-ld=lld -g
*/

#include <cuda_runtime.h>

#include <iostream>
#include <string>
#include <vector>

#include <clang/Frontend/CompilerInvocation.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Lex/PreprocessorOptions.h>
#include <clang/Basic/DiagnosticOptions.h>
#include <clang/Frontend/TextDiagnosticPrinter.h>
#include <clang/CodeGen/CodeGenAction.h>
#include <clang/Basic/TargetInfo.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/TargetSelect.h>

// JIT
#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/ExecutionEngine/Orc/ThreadSafeModule.h>
#include "llvm/ExecutionEngine/Orc/DebugUtils.h"
#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/TargetSelect.h"
#include <llvm/Support/raw_ostream.h>

using namespace std;
using namespace clang;
using namespace llvm;
using namespace llvm::orc;

int main() {
    // Code to be JIT'ed
    constexpr auto testCodeFileName = "test.cu";
    constexpr auto testCode = "extern \"C\" __attribute__((global)) void test(int *x) { *x *= 2; }";

    InitializeAllTargetMCs();
    InitializeAllAsmPrinters();

    // Command line arguments for clang
    vector<const char *> args;
    args.push_back(testCodeFileName);
    args.push_back("-O3");
    args.push_back("-I/usr/local/cuda/include");
    args.push_back("-I/usr/local/include");
    // args.push_back("--cuda-gpu-arch=sm_75"); // hint to ptx

    // It depends on whole lot of classes, to do its job
    DiagnosticOptions DiagOpts;
    TextDiagnosticPrinter *textDiagPrinter =
            new clang::TextDiagnosticPrinter(errs(),
                                         &DiagOpts);
    IntrusiveRefCntPtr<clang::DiagnosticIDs> pDiagIDs;
    DiagnosticsEngine *pDiagnosticsEngine =
            new DiagnosticsEngine(pDiagIDs,
                                         &DiagOpts,
                                         textDiagPrinter);

    // CompilerInvocation init
    CompilerInvocation *CI = new CompilerInvocation();
    ArrayRef<const char *> aref(args.data(), args.data() + args.size());
    CompilerInvocation::CreateFromArgs(*CI, aref, *pDiagnosticsEngine);

    // Code is in Memory and is being converted to IR
    StringRef testCodeData(testCode);
    unique_ptr<MemoryBuffer> buffer = MemoryBuffer::getMemBufferCopy(testCodeData);
    CI->getPreprocessorOpts().addRemappedFile(testCodeFileName, buffer.get());


    // Init CompilerInstance, the sheer number of classes is staggering.
    CompilerInstance Clang;
    std::shared_ptr<CompilerInvocation> ciptr(CI);
    Clang.setInvocation(ciptr);
    Clang.createDiagnostics();

    // Set target as x86, can be changed to desired
    InitializeAllTargets();
    const std::shared_ptr<clang::TargetOptions> targetOptions = std::make_shared<clang::TargetOptions>();
    targetOptions->Triple = string("nvvm");
    TargetInfo *pTargetInfo = TargetInfo::CreateTargetInfo(*pDiagnosticsEngine,targetOptions);
    Clang.setTarget(pTargetInfo);

    // Create and execute action
    CodeGenAction *compilerAction = new EmitLLVMOnlyAction();
    // CodeGenAction *compilerAction = new EmitAssemblyAction(); // this will create an assemble file as well.
    Clang.ExecuteAction(*compilerAction);
    auto module = compilerAction->takeModule();
    module->dump(); // Print out the IR

    // Try to detect the host arch and construct an LLJIT instance.
    auto JIT = LLJITBuilder().create();

    // If we could not construct an instance, return an error.
    if (!JIT) {
        //(JIT.takeError());
        cout << "Error in creating JIT" << endl;
        return 0;
    }
    // We need context now
    auto Ctx = std::make_unique<LLVMContext>();

    // Add the module.
    if (auto Err = JIT.get()->addIRModule(ThreadSafeModule(std::move(module), std::move(Ctx)))) {
        std::cout  << " Failed in adding IR to JIT" << endl;
        return 0;
        // return Err;
    }

    // Look up the JIT'd code entry point, mangled name at the moment, have to fix this
    auto EntrySym = JIT.get()->lookup("test");
    if (!EntrySym) {
        cout << "Couldnt find symbol" << endl;
        //return EntrySym.get().takeError();
        return 0;
    }

    // Cast the entry point address to a function pointer.
    auto *Entry = (void(*)(int*))EntrySym.get().getAddress();
    if(!Entry) {
        cout << "failed to materailize symbol" << endl;
    }

    // Call into JIT'd code.
    // cout << "OP of JIT:: " << Entry(2) << endl;;
    // int x = 2;
    // int *d_x;
    // cudaMalloc(&d_x, sizeof(int));
    // cudaMemcpy(d_x, &x, sizeof(int), cudaMemcpyHostToDevice);
    // Entry<<<1,1>>>(d_x);
    // cudaMemcpy(&x, d_x, sizeof(int), cudaMemcpyDeviceToHost);
    // cout <<  "Output of JIT kernel::"  << x << endl;
    buffer.release();
}