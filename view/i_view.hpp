//
//  i_view.hpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#ifndef i_view_hpp
#define i_view_hpp

class i_view {
    
public:
    i_view(): update_cnt(0) { }
    
    virtual bool init() = 0;
    virtual void update() = 0;
    
protected:
    
    int update_cnt;
};

#endif /* i_view_hpp */
