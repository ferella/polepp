#include "Pdf.h"

namespace PDF {

Poisson::Poisson() {
  m_data = 0; // for the destructor
  m_nN = 0;   // makes sure if we call getVal without having done init(), it will still function
  m_nTot = 0;
  m_nLambda = 0;
}

Poisson::~Poisson() {
  if (m_data) delete [] m_data;
}

void Poisson::init(int nlambda, int nn, double lmax) {
  m_nLambda = nlambda;
  m_nN = nn;
  m_nTot = nn*nlambda;
  m_lambdaMax = lmax;
  //
  m_data = new double[m_nTot];
  //
  m_dL = m_lambdaMax/double(m_nLambda);
  //
  double lmb;
  unsigned long index;
  std::cout << "==================================" << std::endl;
  if (m_nTot==0) {
    std::cout << " Will not use tabulated poisson!" << std::endl;
  } else {
    std::cout << " Initialising poisson table with:" << std::endl;
    std::cout << "   n(lambda)  = " << m_nLambda <<std::endl;
    std::cout << "   lambda_max = " << m_lambdaMax <<std::endl;
    std::cout << "   n(N)       = " << m_nN <<std::endl;
    for (unsigned long i=0; i<m_nLambda; i++) {
      lmb = m_dL*double(i);
      for (unsigned long j=0; j<m_nN; j++) {
	index = i*m_nN +j;
	m_data[index] = rawPoisson(int(j),lmb);
      }
    }
  }
  std::cout << "==================================\n" << std::endl;
}

double Poisson::rawPoisson(int n, double s) {
  double prob;
  if(s<50.0) {
    prob = (pow(s,n)/exp(lgamma(n+1)))*exp(-s);
  } else {
    double sigma = sqrt(s); // gaussian aprox.
    double c = 1.0L/(sqrt(2.0*M_PI)*sigma);
    double t = (double(n)-s)/sigma;
    prob = c*exp(-0.5L*t*t);
  }
  return prob;
}

Gauss::Gauss() {
  m_data = 0;    // for the destructor
  m_nData = 0;   // makes sure if we call getVal without having done init(), it will still function
}

Gauss::~Gauss() {
  if (m_data) delete [] m_data;
}

void Gauss::init(int ndata, double mumax) {
  double mu;

  m_nData = ndata;
  m_muMax = mumax;
  m_dMu = m_muMax/double(m_nData);
  //
  std::cout << "==================================" << std::endl;
  if (m_nData==0) {
    std::cout << " Will not use tabulated gauss!" << std::endl;
  } else {
    m_data = new double[m_nData];
    std::cout << " Initialising gauss table with:" << std::endl;
    std::cout << "   n data     = " << m_nData <<std::endl;
    std::cout << "   mu max     = " << m_muMax <<std::endl;
    for (unsigned long i=0; i<m_nData; i++) {
      mu = m_dMu*double(i);
      m_data[i] = rawGauss(mu);
    }
  }
  std::cout << "==================================\n" << std::endl;
}

double Gauss::rawGauss(double mu) {
  double prob;
  double norm = 1.0L/sqrt(2.0*M_PI);
  prob = norm*exp(-0.5L*mu*mu);
  return prob;
}

};
