#ifndef INTERPOLATION_VECTOR_LABS_CPP
#define INTERPOLATION_VECTOR_LABS_CPP

#include "vector.h"


using namespace std;

/* ----------------------------------------------------------------------------------------------------
 *  @greetings      Glad to see you here!
 *                  Welcome Vector specialisation for your physics Labs
 *
 *  @features       @@First:
 *                  You should type certain number of dots
 *                  and then, using "get_dots(...)" you will get file
 *                  with approximated/modulated dots, between dots, which you had typed
 *
 *                  @@Second:
 *                  Example of overloaded operator[]
 *                  it can take Integer position (for typing dots)
 *                  and Double Position (to get modulateted dots)
 *
 *                  @@Note!
 *                  Operator [] for double Position returns copies of objects
 *                  NOT LINKS!
 *
 *                  @@Third:
 *                  class Point is also implemented here
 *
 *                  @@Fourth:
 *                  output to .tex file
 *
 *                  @@Fifth
 *                  use .set_mode(MODE) to  set mode of using
 *
 *
 *  @modes          LINEAR.......................Linear Approximation
 *                  BEZIER_OPTIMAL...............Approximation with 3rd degree Bezier curves
 *                  BEZIER_PARABOLIC.............Approximation with 2rd degree Bezier curves
 *                  CATMULL-ROM..................Approximation with special 3rd degree Catmull-Rom curves
 *                  PARABOLIC....................Building parabols with every three dots
 *                  CURVE_MODE_DEFAULT...........Default mode
 *
 *
 * @notes:
 *      @@cetrain_amount_of_dots - There are CERTAIN amounts of dots for each mode
 *
 *                  N  - is amount of dots
 *
 *                  LINEAR....................... (N > 0)
 *                  BEZIER_OPTIMAL............... (N > 3) and (N % 3 == 1)
 *                  BEZIER_PARABOLIC............. (N > 2) and (N % 2 == 1)
 *                  CATMULL_ROM.................. (N > 3)
 *                  PARABOLIC.................... (N > 2) and (N % 2 == 1)
 *                  CURVE_MODE_DEFAULT........... (N > 0)
 *
 *
 *
 /------------------------------------------------------------------------------------------------*/
enum CURVE_MODE
{
    LINEAR = 0,
    BEZIER_PARABOLIC,
    BEZIER_OPTIMAL,
    CATMULL_ROM,
    PARABOLIC,
    CURVE_MODE_DEFAULT
};

const double EPSILON = 10e-5;

const char* VECTOR_LABS_LOG_FILE = "vector_labs_log.txt";

/* --------------------------------------------------------------------------------------
 *  @about class Point, main class of Vector in Lab mode,
 *         Heart of this project
 *
 *
 *
 /-----------------------------------------------------------------------------------------*/
class Point {
public:
    double x_ = NAN;
    double y_ = NAN;
    Point() {};

    Point(const double& x, const double& y):
            x_(x),
            y_(y)
    {};

    Point(const Point& that):
            x_(that.x_),
            y_(that.y_)
    {};

    ~Point(){
        x_ = NAN;
        y_ = NAN;
    }


    Point& operator = (Point that)
    {
        swap(that);
    };

    Point& operator += (Point that){
        x_ += that.x_;
        y_ += that.y_;
    }

    Point& operator *= (const double& multiplicator){
        x_ *= multiplicator;
        y_ *= multiplicator;
    }

    void swap(Point& that)
    {
        std::swap(x_, that.x_);
        std::swap(y_, that.y_);
    }



    friend Point operator + (const Point& left, const Point& right)
    {
        auto result = left;
        result += right;

        return result ;
    }

 /*
    friend Point operator * (Point left, const double multiplicator)
    {
        auto result = left
        left *= multiplicator;
        return left;
    }

    friend Point operator * (const double multiplicator, Point right)
    {
        right *= multiplicator;
        return right;
    }

    */

    friend ostream &operator<<(ostream& out, const Point& that)
    {
        out<<that.x_<<" "<<that.y_<<endl;
        return out;
    }

    friend istream &operator>>(istream& in, Point& that)
    {
        in>>that.x_>>that.y_;
        return in;
    }
};


/* -------------------------------------------------------
 *  @about  Vector<Point> specialisation
 *          To be exact Vector<Point>
 *          body of this project
 *
 *
 *  @note A lot of special functions
 /------------------------------------------------------*/
template <>
class Vector <Point> {
private:
    Point* buffer_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
    enum CURVE_MODE lab_mode_ = CURVE_MODE_DEFAULT;

    /* buffer to collect factors for curves in some modes*/
    double* staff_buffer_;
    
    /* procedure of calculating and collecting this factors */
    void get_factors(enum CURVE_MODE mode);

public:
    Vector() {};

    explicit inline Vector(size_t capacity);

    inline Vector(const Vector& that);

    inline Vector(Vector&& victim);

    inline ~Vector();

    Point operator[] (double pos);

    Point& operator [] (int pos);

    inline bool operator == (const Vector& that);

    inline bool operator != (const Vector& that);

    inline Vector& operator = (Vector victim)
    {
        swap(victim);

        if (*this != victim)
        {
            throw new Acorn(LOGIC_ERROR, "operator = hadn't worked\n",
                                  __PRETTY_FUNCTION__,__FILE__,__LINE__, nullptr);
        }
    }

    inline Vector& operator = (Vector&& victim)
    {
        swap(victim);

        if (*this != victim)
        {
            throw new Acorn(LOGIC_ERROR, "operator = hadn't worked\n",
                            __PRETTY_FUNCTION__,__FILE__,__LINE__, nullptr);
        }
    }


    inline void swap(Vector& that);

    void set_mode(enum CURVE_MODE mode);

    void get_dots(FILE* output, enum CURVE_MODE mode, const double sampling);
};



/* -------------------------------------------------------
 *  @about Constructor for Vector<Point> class in Lab Mode
 *         Construct Vector using needed capacity
 *
 *
 *  @note fill with start values
 /------------------------------------------------------*/
inline Vector<Point>::Vector(size_t capacity):
    buffer_  (new Point [capacity]),
    size_ (0),
    capacity_ (capacity),
    lab_mode_ (CURVE_MODE_DEFAULT)
{
    //printf("I am Lab-Killer constructor of your dream,\n"
                   //"Constructed one Vector with capacity [%d] \n\n", capacity_);
}


/* -------------------------------------------------------
 *  @about  Copy Constructor for Vector<Point> class
 *          Construct Vector using another Vector
 *
 *  @note for long-live objects
 /------------------------------------------------------*/
inline Vector<Point>::Vector(const Vector& that)           // use std::copy
{
    Vector victim(that.capacity_);
    memcpy(victim.buffer_, that.buffer_, that.capacity_ );
    swap(victim);
    //printf("Copy constructor in Lab Mode,\n"
    //               "Created object with size [%d]\n\n", that.capacity_);
};


/* -------------------------------------------------------
 *  @about Copy operator for Vector<Point>
 *
 *  @note Specially for objects with short life
 *
 *
 /--------------------------------------------------------*/
inline Vector<Point>::Vector(Vector&& victim):
        buffer_  (victim.buffer_),
        size_    (victim.size_),
        capacity_ (victim.capacity_),
        lab_mode_(victim.lab_mode_)
{
    //printf("Weird stealing constructor in Lab Mode\n\n");
    victim.buffer_ = nullptr;
}



/* -------------------------------------------------------
 *  @about Destructor for Vector<Point> in Lab mode class
 *
 *  @note Write about deleting objects to control the situation
 *
 /------------------------------------------------------*/
inline Vector<Point>::~Vector()
{
    //printf("Vector destructor: Destructed Vector with capacity: [%d]\n", capacity_);
    //printf("And Sizeof: [%d] bytes\n\n", sizeof(double)*capacity_);

    delete [] buffer_;
    buffer_ = nullptr;
    capacity_ = 0;
    size_ = 0;
}



/* -------------------------------------------------------
 *  @about operator == for Vector
 *
 *
 *
 /------------------------------------------------------*/
inline bool Vector<Point>::operator == (const Vector& that)
{
    if ((this->buffer_ != that.buffer_)
        && (this->capacity_!= that.capacity_)
        && (this->staff_buffer_ != that.staff_buffer_)
        && (this->lab_mode_ != that.lab_mode_))
    {
        return 1;
    }
    else
    {
         return 0;
    }
}

/* -------------------------------------------------------
 *  @about operator != for Vector
 *
 *
 *
 /------------------------------------------------------*/
inline bool Vector<Point>::operator != (const Vector& that)
{
    if (!(*this == that))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


/* ------------------------------------------------------------------------------
 *  @about Modified operator[] for Vector<Point> labs mode
 *
 *  @return Modeled Interpolated dots
 *
 *  @note
 *
 /-------------------------------------------------------------------------------*/
inline Point Vector<Point>::operator[] (double pos) {
    switch (lab_mode_)
    {
        case CURVE_MODE_DEFAULT :
            {
                if (((int)pos < 0) || ((int)pos >= capacity_))
                {
                    throw new Acorn(MEMORY_ACCES_ERROR, "Index out of range!\n",
                                    __PRETTY_FUNCTION__,__FILE__,__LINE__, nullptr);
                }
                if((pos - (int)pos ) > EPSILON)
                {
                    throw new Acorn(LOGIC_ERROR, "You haven't choosen mode of using\n",
                                    __PRETTY_FUNCTION__,__FILE__,__LINE__, nullptr);
                }

                return buffer_[(int) pos];
            }
            break;
            
        case LINEAR :
            {

                if (((int)pos < 0) || ((int)pos >= capacity_))
                {
                    throw new Acorn(MEMORY_ACCES_ERROR, "LINEAR mode, Index out of range!\n",
                                    __PRETTY_FUNCTION__,__FILE__,__LINE__, nullptr);
                }

                auto position = (int)trunc(pos);
                auto t = pos - (double)position;

                Point P;
                P.x_ = (1 - t) * buffer_[position].x_  + t * buffer_[position + 1].x_;
                P.y_ = (1 - t) * buffer_[position].y_  + t * buffer_[position + 1].y_;

                return P;
            }
            break;

        case BEZIER_PARABOLIC :
        {
            if (((int)pos < 0) || ((int)pos > capacity_))
            {
                throw new Acorn(MEMORY_ACCES_ERROR, "BEZIER_PARABOLIC mode, Index out of range!\n",
                                __PRETTY_FUNCTION__,__FILE__,__LINE__, nullptr);
            }

            if ((capacity_ < 3) || (capacity_ % 2 != 1))
            {
                throw new Acorn(MEMORY_ACCES_ERROR, "Invalid amount of dots!\n"
                                        "In BEZIER_PARABOLIC mode amount of dots must be N: (N % 2 == 1)&&(N > 2)\n",
                                __PRETTY_FUNCTION__,__FILE__,__LINE__, nullptr);
            }


            int DEGREE = 2;
            auto position = DEGREE * ((int)trunc(pos) / DEGREE);
            auto t = (pos - position) / DEGREE;

            Point P;
            P.x_ = (1 - t) * (1 - t) * buffer_[position].x_
                    + 2 * t * (1 - t)* buffer_[position + 1].x_
                    + t * t * buffer_[position + 2].x_;

            P.y_ = (1 - t) * (1 - t) * buffer_[position].y_
                   + 2 * t * (1 - t)* buffer_[position + 1].y_
                   + t * t * buffer_[position + 2].y_;

            return P;
        }
        break;
            
        case BEZIER_OPTIMAL:
        {
            if (((int)pos < 0) || ((int)pos > capacity_))
            {
                throw new Acorn(MEMORY_ACCES_ERROR, "BEZIER_OPTIMAL mode, Index out of range!\n",
                                __PRETTY_FUNCTION__,__FILE__,__LINE__, nullptr);
            }

            if ((capacity_ < 4) || (capacity_ % 3 != 1))
            {
                throw new Acorn(MEMORY_ACCES_ERROR, "Invalid amount of dots!\n"
                                        "In BEZIER_OPTIMAL mode amount of dots must be N: (N % 3 == 1)&&(N > 3)\n",
                                __PRETTY_FUNCTION__,__FILE__,__LINE__, nullptr);
            }

            int DEGREE = 3;
            auto position = DEGREE * ((int)trunc(pos) / DEGREE);
            auto t = (pos - position) / DEGREE;


            Point P;
            P.x_ = (1 - t) * (1 - t) * (1 - t) * buffer_[position].x_
                   + 3 * t * (1 - t)* (1 - t) * buffer_[position + 1].x_
                   + 3 * t * t* (1 - t) * buffer_[position + 2].x_
                   + t * t * t * buffer_[position + 3].x_;

            P.y_ = (1 - t) * (1 - t) * (1 - t) * buffer_[position].y_
                   + 3 * t * (1 - t)* (1 - t) * buffer_[position + 1].y_
                   + 3 * t * t* (1 - t) * buffer_[position + 2].y_
                   + t * t * t * buffer_[position + 3].y_;

            return P;
        }
        break;
        case PARABOLIC:
        {
            if (((int)pos < 0) || ((int)pos > capacity_))
            {
                throw new Acorn(MEMORY_ACCES_ERROR, "PARABOLIC mode, Index out of range!\n",
                                __PRETTY_FUNCTION__,__FILE__,__LINE__, nullptr);
            }

            if ((capacity_ < 3) || (capacity_ % 2 != 1))
            {
                throw new Acorn(MEMORY_ACCES_ERROR, "Invalid amount of dots!\n"
                                        "In PARABOLIC mode amount of dots must be N: (N % 2 == 1)&&(N > 2)\n",
                                __PRETTY_FUNCTION__,__FILE__,__LINE__, nullptr);
            }

            int DEGREE = 2;
            auto position = DEGREE * ((int)trunc(pos) / DEGREE);

            auto delta_x = buffer_[position + 2].x_ - buffer_[position].x_;
            double x = buffer_[position].x_ + ((pos - position) / DEGREE) * delta_x;

            int staff_i = (position / 2) * 3;

            Point P;
            P.x_ = x;
            P.y_ = staff_buffer_[staff_i] * x * x + staff_buffer_[staff_i + 1] * x + staff_buffer_[staff_i + 2];

            return P;
        }
        break;
        case CATMULL_ROM:
        {
            if (((int)pos < 0) || ((int)pos > capacity_))
            {
                throw new Acorn(MEMORY_ACCES_ERROR, "CATMULL_ROM mode, Index out of range!\n",
                                __PRETTY_FUNCTION__,__FILE__,__LINE__, nullptr);
            }

            if (capacity_ < 3)
            {
                throw new Acorn(MEMORY_ACCES_ERROR, "Invalid amount of dots!\n"
                                        "In CATMULL_ROM mode amount of dots must be N: (N > 3)\n",
                                __PRETTY_FUNCTION__,__FILE__,__LINE__, nullptr);
            }

            auto position = (int)trunc(pos);
            auto t = pos - trunc(pos);

            Point P;
            P.x_ = 0.5 * ( (-1) * t * (1 - t) * (1 - t) * buffer_[position].x_
                   + (2 - 5 * t * t + 3 * t * t * t) * buffer_[position + 1].x_
                   + t * (1 + 4 * t - 3 * t * t) * buffer_[position + 2].x_
                   - t * t * (1 - t) * buffer_[position + 3].x_ );

            P.y_ =  0.5 * ((-1) * t * (1 - t) * (1 - t) * buffer_[position].y_
                    + (2 - 5 * t * t + 3 * t * t * t) * buffer_[position + 1].y_
                    + t * (1 + 4 * t - 3 * t * t) * buffer_[position + 2].y_
                    - t * t * (1 - t) * buffer_[position + 3].y_);

            return P;

        }

    }
    

}



/* --------------------------------------------------------------------------------------------------------------
 *  @about Function to configure output file with dots
 *
 *
 *  @note
 *
 /------------------------------------------------------------------------------------------------------------*/

#define WRITE_TO_FILE(ITERATION_START, ITERATION_END)\
    Point P;\
    fprintf(output,"\\documentclass[a4paper,12pt]{article}\n"\
                    "\\usepackage{float}\n"\
                    "\\usepackage{pgfplots}\n"\
                    "% Preamble: \\pgfplotsset{width=1cm,compat=newest}\n"\
                    "\\begin{document}\n" \
                    "\\begin{tikzpicture}\n"\
                    "\\begin{axis}[height=15cm,width=15cm,grid=major]\n"\
                    "\\addlegendentry{gpaphic}\n"\
                    "\\addplot[color = blue, mark = * ] coordinates {\n");\
\
    for (double j = ITERATION_START; j <= ITERATION_END; j += sampling)\
    {\
        P = this->operator[](j);\
        fprintf(output,"(%f,%f)\n", P.x_, P.y_);\
    }\
    fprintf(output, "};\n\n"\
                    "\\addlegendentry{dots}\n"\
                    "\\addplot[color = red, mark = * ] coordinates {\n"); \
    for (int i = 0; i < capacity_; i ++)\
    {\
        P = this->operator[](i);\
        fprintf(output,"(%f,%f)\n", P.x_, P.y_);\
    }\
    fprintf(output, "};\n\n"\
                    "\\end{axis}\n"\
                    "\\end{tikzpicture}\n"  \
                    "\\end{document}\n"); \


inline void Vector<Point>::get_dots(FILE* output, enum CURVE_MODE mode, const double sampling)
{
    try {
        switch (mode) {
            case LINEAR: {
                set_mode(LINEAR);

                WRITE_TO_FILE(0, capacity_ - 1)
            }
                break;

            case PARABOLIC: {
                set_mode(PARABOLIC);

                WRITE_TO_FILE(0, capacity_ - 1)
            }
                break;

            case BEZIER_OPTIMAL: {

                set_mode(BEZIER_OPTIMAL);

                WRITE_TO_FILE(0, capacity_ - 1)

                set_mode(CURVE_MODE_DEFAULT);
            }
                break;

            case BEZIER_PARABOLIC: {

                set_mode(BEZIER_PARABOLIC);

                WRITE_TO_FILE(0, capacity_ - 1)

                set_mode(CURVE_MODE_DEFAULT);
            }
                break;

            case CATMULL_ROM: {

                set_mode(CATMULL_ROM);

                WRITE_TO_FILE(0, capacity_ - 3)

                set_mode(CURVE_MODE_DEFAULT);
            }
                break;
        }
    }

    catch(Acorn* acorn)
    {
        throw new Acorn(LOGIC_ERROR, "Error while getting dots\n",
                __PRETTY_FUNCTION__,__FILE__,__LINE__, acorn);
    }
}
#undef WRITE_TO_FILE

/* -------------------------------------------------------------
 *  @about Setting mode of using for Vector 
 *         Preparing some factors
 *
 *  @note
 *
 /----------------------------------------------------------------*/
inline void Vector<Point>::set_mode (enum CURVE_MODE mode)
{
    //printf("Mode changed from [%d] to [%d]\n\n", lab_mode_, mode);
    lab_mode_ = mode;
    if (mode == PARABOLIC)
        {
            staff_buffer_ = new double [3 * (capacity_ / 2)];
            get_factors(PARABOLIC);
        }
    
}

/* -----------------------------------------------------------------------------
 *  @about Calculating and packaging some factors for Interpolating curves
 *
 *
 *  @note
 *
 /-----------------------------------------------------------------------------------*/
#define DETERMINANT(a,b,c,d,e,g,h,i,j)\
    a * (e * j - g * i) - b * ( d * j - g * h) + c * (d * i - e * h)
void Vector<Point>::get_factors(enum CURVE_MODE mode){
    switch(mode)
    {
        case PARABOLIC :
        {
            int buffer_i = 0;
            for (int staff_i = 0; staff_i < 3 *( capacity_ / 2); staff_i += 3)
            {
                double x0 = buffer_[buffer_i].x_;
                double y0 = buffer_[buffer_i].y_;
                double x1 = buffer_[buffer_i + 1].x_;
                double y1 = buffer_[buffer_i + 1].y_;
                double x2 = buffer_[buffer_i + 2].x_;
                double y2 = buffer_[buffer_i + 2].y_;


                double det = DETERMINANT(x0 * x0, x0, 1, x1 * x1, x1 , 1, x2* x2, x2, 1);
                double det_a = DETERMINANT(y0, x0, 1, y1, x1 , 1, y2, x2, 1);
                double det_b = DETERMINANT(x0 * x0, y0, 1, x1 * x1, y1 , 1, x2* x2, y2, 1);
                double det_c = DETERMINANT(x0 * x0, x0, y0, x1 * x1, x1 ,y1, x2* x2, x2, y2);

                if (det == 0)
                {
                    throw new Acorn(LOGIC_ERROR, "Parabolic method isn't appropriate in your case\n",
                            __PRETTY_FUNCTION__,__FILE__,__LINE__, nullptr);
                }

                staff_buffer_[staff_i] = det_a / det;
                staff_buffer_[staff_i + 1] = det_b / det;
                staff_buffer_[staff_i + 2] = det_c / det;

                buffer_i += 2;
            }

        }
        break;
    }
}
#undef DETERMINANT

/* -------------------------------------------------------------
 *  @about Modified operator[] for Vector<double> labs mode
 *         for Int pos argument, to configure Vector
 *
 *  @note
 *
 /----------------------------------------------------------------*/
inline Point& Vector<Point>::operator [](int pos)
{
    if ((pos < 0) || (pos > capacity_))
    {
        throw new Acorn(MEMORY_ACCES_ERROR, "operator[](int pos), Index out of range!\n",
                        __PRETTY_FUNCTION__,__FILE__,__LINE__, nullptr);

    }


    return buffer_[pos];
}


/* -------------------------------------------------------
 *  @about Swap procedure for move semantics
 *
 *
 *  @note swap all internal fields
 /------------------------------------------------------*/

inline void Vector<Point>::swap(Vector& that)
{
    std::swap(size_,that.size_);
    std::swap(capacity_, that.capacity_);
    std::swap(buffer_, that.buffer_);
    std::swap(staff_buffer_, that.staff_buffer_);
    std::swap(lab_mode_, that.lab_mode_);
}


#endif // INTERPOLATION_VECTOR_LABS_CPP