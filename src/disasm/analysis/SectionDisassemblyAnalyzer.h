//===------------------------------------------------------------*- C++ -*-===//
//
// This file is distributed under BSD License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// 
// Copyright (c) 2016 University of Kaiserslautern.

#pragma once
#include "MaximalBlockCFGNode.h"
#include "DisassemblyCFG.h"

namespace disasm {

class SectionDisassembly;
class RawInstAnalyzer;

/**
 * SectionDisassemblyAnalyzer
 */
class SectionDisassemblyAnalyzer {
public:
    SectionDisassemblyAnalyzer() = delete;
    explicit SectionDisassemblyAnalyzer
        (SectionDisassembly *sec_disasm,
         const RawInstAnalyzer *analyzer,
         const std::pair<addr_t, addr_t> &exec_region);
    virtual ~SectionDisassemblyAnalyzer() = default;
    SectionDisassemblyAnalyzer
        (const SectionDisassemblyAnalyzer &src) = default;
    SectionDisassemblyAnalyzer
        &operator=(const SectionDisassemblyAnalyzer &src) = default;
    SectionDisassemblyAnalyzer(SectionDisassemblyAnalyzer &&src) = default;

    void BuildCFG();
    /*
     * Search in CFG to find direct successor
     */
    MaximalBlockCFGNode *findDirectSuccessor
        (const MaximalBlockCFGNode &cfg_node) noexcept;
    /*
     * Search in CFG to find remote successor matching target
     */
    MaximalBlockCFGNode *findRemoteSuccessor(addr_t target) noexcept;

    void RefineCFG();
    void RefineMaximalBlocks(const std::vector<addr_t> &known_code_addrs);
    bool isValidCodeAddr(addr_t addr) const;
    const DisassemblyCFG &getCFG() const noexcept;

private:
    /*
     * Finds a valid basic block in and invalidates all direct predecessors that
     * do not target it.
     */
    void SetValidBasicBlock(MaximalBlockCFGNode &node);
    void ResolveCFGConflict(MaximalBlockCFGNode &node);
private:
    SectionDisassembly *m_sec_disassembly;
    const RawInstAnalyzer * m_analyzer;
    addr_t m_exec_addr_start;
    addr_t m_exec_addr_end;
    DisassemblyCFG m_sec_cfg;
};
}



