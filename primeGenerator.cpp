#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

typedef unsigned int UINT;

const UINT MAXPRIMENUMBERS = 1000000000;
const UINT SQUAREMAXPRIMENUMBERS = 10000000;
const UINT BUFFERSIZE = 20000; 

void crossOut(UINT p, UINT b, bool mark[]) 
{
  UINT si = (p - (b % p)) % p;
  
  if (si & 1)
  {
    si += p;
  }
  
  if (p*p > b)
  {
    si = max(si, p*p-b);
  }

  for (UINT i = si/2; i < BUFFERSIZE/2; i += p)
  {
    mark[i] = true;
  }
}

void calculatePrimes() 
{
  int primeCount = 1; UINT lastPrimeNumber = 2;

  vector<UINT> primesList; 
  primesList.push_back(2);

  bool mark[BUFFERSIZE/2] = {false};
  
  for (UINT i = 1; i < BUFFERSIZE/2; ++i)
  {
    if (!mark[i]) 
    {
      ++primeCount; lastPrimeNumber = 2*i+1;
      primesList.push_back(lastPrimeNumber);
      if (lastPrimeNumber*lastPrimeNumber <= BUFFERSIZE)
      {
        crossOut(2*i + 1, 1, mark);
      }
    }
    else 
    {
      mark[i] = false;
    }
  }

  for (UINT b = 1+BUFFERSIZE; b < MAXPRIMENUMBERS; b += BUFFERSIZE) 
  {
    for (UINT i = 1; primesList[i]*primesList[i] < b+BUFFERSIZE; ++i)
    {
      crossOut(primesList[i], b, mark);
    }
    
    for (UINT i = 0; i < BUFFERSIZE/2; ++i)
    {
      if (!mark[i]) 
      {
        ++primeCount; 
        lastPrimeNumber = 2*i + b;
        if (lastPrimeNumber <= SQUAREMAXPRIMENUMBERS)
        {
          primesList.push_back(lastPrimeNumber);
        }
      }
      else 
      {
        mark[i] = false;
      }
    }
  }

  cout << "Found " << primeCount << " primes in total.\n";
  cout << "Recorded " << primesList.size() << " primes, up to " << SQUAREMAXPRIMENUMBERS << '\n';
  cout << "Last prime found was " << lastPrimeNumber << '\n';
  }

int main() 
{
  cout << "ShadowShack PrimeGenerator"
  unsigned int start = clock();
  calculatePrimes();
  cout << "Time taken in millisecs: " << clock()-start
  system("pause");
  return 0;
}
