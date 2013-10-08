/*********************                                                        */
/*! \file cnf_proof.h
 ** \verbatim
 ** Original author: Liana Hadarean
 ** Major contributors: Morgan Deters
 ** Minor contributors (to current version): none
 ** This file is part of the CVC4 project.
 ** Copyright (c) 2009-2013  New York University and The University of Iowa
 ** See the file COPYING in the top-level source directory for licensing
 ** information.\endverbatim
 **
 ** \brief A manager for CnfProofs.
 **
 ** A manager for CnfProofs.
 **
 ** 
 **/

#ifndef __CVC4__CNF_PROOF_H
#define __CVC4__CNF_PROOF_H

#include "cvc4_private.h"
#include "util/proof.h"
#include "proof/sat_proof.h"

#include <ext/hash_set>
#include <ext/hash_map>
#include <iostream> 

namespace CVC4 {
namespace prop {
class CnfStream;
}

typedef __gnu_cxx::hash_map < ClauseId, const prop::SatClause* > IdToClause; 
typedef __gnu_cxx::hash_set<prop::SatVariable > VarSet;

class TheoryProof; 
  
class CnfProof {
protected:
  CVC4::prop::CnfStream* d_cnfStream;
  IdToClause d_inputClauses;
  IdToClause d_theoryLemmas;
  VarSet     d_propVars;
  TheoryProof* d_theoryProof;
  TheoryProof* getTheoryProof();

  Expr getAtom(prop::SatVariable var);
public:
  CnfProof(CVC4::prop::CnfStream* cnfStream);
  void addClause(ClauseId id, const prop::SatClause* clause, ClauseKind kind);
  void addVariable(prop::SatVariable var); 
  void setTheoryProof(TheoryProof* theory_proof);
  virtual void printAtomMapping(std::ostream& os, std::ostream& paren) = 0;
  virtual void printClauses(std::ostream& os, std::ostream& paren) = 0;
  virtual ~CnfProof(); 
};

class LFSCCnfProof: public CnfProof {
  void printInputClauses(std::ostream& os, std::ostream& paren);
  void printTheoryLemmas(std::ostream& os, std::ostream& paren);
  void printClause(const prop::SatClause& clause, std::ostream& os, std::ostream& paren);
public:
  LFSCCnfProof(CVC4::prop::CnfStream* cnfStream)
    : CnfProof(cnfStream)
  {}
  virtual void printAtomMapping(std::ostream& os, std::ostream& paren);
  virtual void printClauses(std::ostream& os, std::ostream& paren);
};

} /* CVC4 namespace */
#endif /* __CVC4__CNF_PROOF_H */
