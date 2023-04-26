//
//  i_time_limited.hpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#ifndef i_time_limited_hpp
#define i_time_limited_hpp

#include <chrono>

class i_time_limited {
    
public:
    i_time_limited(): start(std::chrono::steady_clock::now()) { }
    
    bool elapsed(double sec) { return sec < (double) ((std::chrono::duration<double>)(std::chrono::steady_clock::now()-start)).count(); }
    void reset( void ) { start = std::chrono::steady_clock::now(); }
    
private:
    
    std::chrono::time_point<std::chrono::steady_clock> start;
};

#endif /* i_time_limited_hpp */
