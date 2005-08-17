#ifndef COMBINE_H
#define COMBINE_H
//
//
//
#include "Combination.h"

class Pole;

class Combine {
 public:
  Combine();
  virtual ~Combine();
  //
  void add(const Pole *point);
  void add(const std::vector<Pole *> poleList);
  //
  void setSmax(double s) {m_sVecMax = s;}
  //
  void init(); // called AFTER all points are added
  void doIt();
  //
  void printResult();
  //
  double getSmax(double s) {return m_sVecMax;}
  //
 private:
  std::vector<const Pole *> m_poleList;
  std::vector<int> m_nVecObs;
  const Pole *m_poleRef; // first Pole object added
  //
  // Vectors for the s(best) scan in n-space
  //
  Range m_bestMuScan;               // scan range in s
  std::vector<double> m_bestMu;     // s(best)
  std::vector<double> m_bestMuProb; // L(n,s(best))
  //
  // Tabulated Likelihood
  //
  Range                              m_sHypRange;
  std::vector<double>                m_sVector;
  std::vector<int>                   m_sMinInd;
  std::vector<int>                   m_sMaxInd;
  std::vector< std::vector<int> >    m_nVectors; // n-vectors used
  std::vector< std::vector<double> > m_likeliHood; // L(n[i],s[j]) = [i][j]
  double m_sVecMax; // max s in sVec (L(n,s)). If < 0 => automatic
  double m_sMaxUsed;// max used sVec == max s(max) encountered

  std::vector<double> m_lhRatio;
  double m_lowerLimit;
  double m_upperLimit;
  bool   m_foundLower;
  bool   m_foundUpper;
  double m_lowNorm;
  double m_uppNorm;
  double m_lowProb;
  double m_uppProb;
  //
  unsigned int m_indexNobs; // index in nVectors of Nobs vector
  //
  void tabulateLikelihood();
  double getLikelihood(int nind, double s);
  unsigned int getNvecIndex(std::vector<int> & nvec) const;

  bool isOK(const Pole *point);

  void setBestMuScan(int ind);
  void findBestMu(int ind); // input vector must be of same size as the poleList
  void findBestMu();

  double calcLimit(double s);
  void findLimits();

};

#endif
