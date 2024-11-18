#pragma once
template<typename _t1>
class Vector2d {
    _t1 x;
    _t1 y;
    public: Vector2d(_t1 new_x, _t1 new_y): x{new_x}, y{new_y} {};
        Vector2d() = default;

        _t1 operator [] (int index) {
            if (index==0){
                return this.x;
            }
            else if (index==1){
                return this.y;
            }
            else {
                throw std::exception{};
            }
        }
        void set(_t1 new_x, _t1 new_y){
            this.x=new_x;
            this.y=new_y;
        } 
        Vector2d operator + (Vector2d other){
            return new Vector2d(this[0]+other[0], this[1]+other[1]);
        }
        Vector2d operator * (Vector2d other){
            return new Vector2d(this[0]*other[0], this[1]*other[1]);
        }
        Vector2d operator - (Vector2d other){
            return new Vector2d(this[0]-other[0], this[1]-other[1]);
        }
        Vector2d operator / (Vector2d other){
            return new Vector2d(this[0]/other[0], this[1]/other[1]);
        }
        bool operator == (Vector2d other){
            return (this[0]==other[0] && this[1]==other[1]);
        }

    };
