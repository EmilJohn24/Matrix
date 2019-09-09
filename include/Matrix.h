#ifndef MATRIX_H
#define MATRIX_H
#include <memory>
#include <vector>
#include <iterator>
#include <iostream>
#include <exception>
#include <numeric>
//due to the lack of random access, std::list is no longer a viable container for this class. As such, its interface will no longer be supported and will return an error at compile-time


template<class T, template<class, class> class Container = std::vector, class Alloc = std::allocator<T>>
class Matrix
{
    public:

        typedef T value_type;
        typedef std::size_t size_type;
        typedef value_type& reference;
        typedef Alloc alloc_type;
        typedef std::shared_ptr<value_type> value_ptr;
        typedef value_ptr& value_ptr_reference;
        typedef Container<value_ptr,  alloc_type> container_type;
        typedef container_type row_type;
        typedef container_type col_type;
        typedef Container<row_type, alloc_type> matrix_row_form;
        typedef Container<col_type, alloc_type> matrix_col_form;
        typedef typename matrix_row_form::iterator row_iterator_type;
        typedef typename matrix_col_form::iterator col_iterator_type;
        typedef typename matrix_row_form::const_iterator const_row_iterator_type;
        typedef typename matrix_col_form::const_iterator const_col_iterator_type;
        typedef typename row_type::iterator inner_row_iterator_type;


        Matrix(const size_type rows = 0, const size_type cols = 0, const value_type& val = value_type());
        row_type& get_row_container(const size_type row);
        col_type& get_col_container(const size_type col);
        Matrix multiply(Matrix& right);

        void insert(row_iterator_type row_start, row_iterator_type row_end,
                        col_iterator_type col_start, col_iterator_type col_end, const value_type& val = value_type());

        value_ptr_reference ptrAt(const size_type row, const size_type col);
        reference at(const size_type row, const size_type col);

        void print(std::ostream& out, char col_sep = ' ', char row_sep = '\n');

        row_iterator_type row_begin(){ return MatRow.begin(); }
        col_iterator_type col_begin(){ return MatCol.begin(); }

        typename matrix_row_form::size_type get_row_count(){ return MatRow.size(); }
        typename matrix_col_form::size_type get_col_count(){ return MatCol.size(); }




       // virtual ~Matrix();

    protected:

    private:
        matrix_row_form MatRow;
        matrix_col_form MatCol;
};


template class Matrix<int>;
template class Matrix<float>;
template<class T, template<class, class> class Container, class Alloc>typename Matrix<T, Container, Alloc>::value_ptr  mat_value_sum(typename Matrix<T, Container, Alloc>::value_ptr first,
                                typename Matrix<T, Container, Alloc>::value_ptr second);

template<class T, template<class, class> class Container, class Alloc>typename Matrix<T, Container, Alloc>::value_ptr  mat_value_prod(typename Matrix<T, Container, Alloc>::value_ptr first,
                                typename Matrix<T, Container, Alloc>::value_ptr second);


#endif // MATRIX_H
