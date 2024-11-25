#pragma once
template<typename _Ty>
    class Vector2d {
        _Ty x;
        _Ty y;
        public: Vector2d(_Ty new_x, _Ty new_y) : x{ new_x }, y{ new_y } {};
                Vector2d() = default;

                _Ty operator [] (int index) const {
                    if (index == 0) {
                        return x;
                    }
                    else if (index == 1) {
                        return y;
                    }
                    else {
                        throw std::exception{};
                    }
                };
                void set(_Ty new_x, _Ty new_y) {
                    x = new_x;
                    y = new_y;
                };
                Vector2d operator + (Vector2d<_Ty> other) const{
                    return Vector2d(x+other[0], y+other[1]);
                }
                Vector2d operator * (_Ty other) const{
                    return Vector2d(x*other, y*other);
                }
                Vector2d operator - (Vector2d<_Ty> other) const{
                    Vector2d result = Vector2d(x - other[0], y - other[1]);
                    return result;
                }
                Vector2d operator / (const _Ty other) const{
                    return Vector2d(x / other, y / other);
                };
                bool operator == (Vector2d<_Ty> other) const{
                    return (x == other[0] && y==other[1]);
                };

            };
    