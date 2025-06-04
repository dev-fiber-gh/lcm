#include <map>
#include <vector>
#include <cstdint>
#include <iostream>


void genPrimesNaive(const uint16_t count, std::vector<uint64_t>& primes) {
    if(0 == primes.size()) {
        primes.push_back(2);
        primes.push_back(3);
    }
    
    uint16_t generated = 0;
    uint64_t next = primes[primes.size() - 1];
    while (generated < count) {
        next += 2;
        
        bool fr = false;
        for(size_t j = 0; j < primes.size(); j++) {
            if(0 == (next % primes[j])) { fr = true; break; } 
        }
        
        if(false == fr) { 
            primes.push_back(next);
            generated++; 
        };
    }
}

uint64_t lcm(std::vector<uint64_t>& values, std::vector<uint64_t>& primes) {
    std::vector<std::map<uint64_t, uint64_t>> valVec; 
    std::map<uint64_t, uint64_t> valMap;
    
    for(size_t i = 0; i < values.size(); i++) {
        uint64_t result = values[i];
        while (result > 1) {
            bool fr = false;
            for(size_t j = 0; j < primes.size(); j++) {
                if(primes[j] <= result) {
                    if(0 == (result % primes[j])) { 
                        valMap[primes[j]]++;
                        result = result / primes[j];
                        fr = true; 
                        break;
                    }
                }
                else break;
            }            
        };
        
        valVec.push_back(std::move(valMap));
    }
    
    
    for(size_t i = 0; i < valVec.size(); i++) {
        for(auto j = valVec[i].begin(); j != valVec[i].end(); j++) {
            if(valMap[j->first] < j->second) valMap[j->first] = j->second;
        }
    }
    
    uint64_t result = 1;
    for(auto i = valMap.begin(); i != valMap.end(); i++) {
        for(uint64_t j = 0; j < i->second; j++) result *= i->first;
    }
    
    return result;
}

int main(int argc, char **argv) {
    std::vector<uint64_t> primes;
    genPrimesNaive(100, primes);

    std::vector<uint64_t> vec =  { 2 , 3 };
    std::cout << lcm(vec, primes) << std::endl;
    
    return 0;
}
