#include "Matrix.h"

template<class T, template<class, class> class Container, class Alloc>
Matrix<T, Container, Alloc>::Matrix(const size_type rows, const size_type cols, const value_type& val): MatRow(rows), MatCol(cols){

    this->insert(MatRow.begin(), MatRow.end(), MatCol.begin(), MatCol.end(), val);
}

//inserter function # 1
template<class T, template<class, class> class Container, class Alloc>
void Matrix<T, Container, Alloc>::insert(row_iterator_type row_start, row_iterator_type row_end,
                                            col_iterator_type col_start, col_iterator_type col_end, const value_type& val){

    if (row_end < row_start || col_end < col_start) throw std::logic_error("The start iterator must come before the end iterator");
    for (row_iterator_type row = row_start; row != row_end; row++){
        for (col_iterator_type col = col_start; col != col_end; col++){
            value_ptr tmp_container = std::make_shared<value_type>(val);
            row->push_back(tmp_container);
            col->push_back(tmp_container);
            RandAccessContainer.push_back(tmp_container);
        }
    }
}

template<class T, template<class, class> class Container, class Alloc>
typename Matrix<T, Container, Alloc>::row_type& Matrix<T, Container, Alloc>::get_row_container(const size_type row){
    if (row >= get_row_count()) throw std::out_of_range("Index out of range.");
    row_iterator_type row_iter = row_begin() + row;
    return *row_iter;
}

template<class T, template<class, class> class Container, class Alloc>
typename Matrix<T, Container, Alloc>::col_type& Matrix<T, Container, Alloc>::get_col_container(const size_type col){
    if (col >= get_col_count()) throw std::out_of_range("Index out of range.");
    col_iterator_type col_iter = col_begin() + col;
    return *col_iter;
}

template<class T, template<class, class> class Container, class Alloc>
typename Matrix<T, Container, Alloc>::value_ptr_reference Matrix<T, Container, Alloc>::ptrAt(const size_type row, const size_type col){
    if (col >= get_col_count() || row >= get_row_count()) throw std::out_of_range("Index out of range.");
    row_type& curr_row = this->get_row_container(row);
    inner_row_iterator_type inner_row_iter = curr_row.begin() + col;
    value_ptr& ptr = *inner_row_iter;
    return ptr;
}

template<class T, template<class, class> class Container, class Alloc>
typename Matrix<T, Container, Alloc>::reference Matrix<T, Container, Alloc>::at(const size_type row, const size_type col){
    value_ptr_reference ptr = ptrAt(row, col);
    return *ptr;

}

template<class T, template<class, class> class Container, class Alloc>
void Matrix<T, Container, Alloc>::print(std::ostream& out, char col_sep, char row_sep){
    for (const row_type &row : MatRow){
        for (const value_ptr val : row) out << *val << col_sep;

        out << row_sep;
    }

}

template<class T, template<class, class> class Container, class Alloc>
typename Matrix<T, Container, Alloc>::value_ptr mat_value_sum(typename Matrix<T, Container, Alloc>::value_ptr first,
                                typename Matrix<T, Container, Alloc>::value_ptr second){
    return std::make_shared<T>(*first + *second);
}

template<class T, template<class, class> class Container, class Alloc>
typename Matrix<T, Container, Alloc>::value_ptr  mat_value_prod(typename Matrix<T, Container, Alloc>::value_ptr first,
                                typename Matrix<T, Container, Alloc>::value_ptr second){
    return std::make_shared<T>(*first * *second);
}

template<class T, template<class, class> class Container, class Alloc>
Matrix<T, Container, Alloc>& Matrix<T, Container, Alloc>::scaled_identity_matrix(const value_type &scalar){
    size_type row_count = this->get_row_count();
    static Matrix identity_tmp;
    identity_tmp = Matrix(row_count, row_count);
    for (size_type i = 0; i != row_count; i++){
        identity_tmp.at(i, i) = scalar;
    }
    return identity_tmp;

}

template<class T, template<class, class> class Container, class Alloc>
auto Matrix<T, Container, Alloc>::multiply(const value_type scalar) -> Matrix{
    Matrix& identity_tmp = scaled_identity_matrix(scalar);
    return identity_tmp.multiply(*this);
}


template<class T, template<class, class> class Container, class Alloc>
auto Matrix<T, Container, Alloc>::multiply(Matrix& right) -> Matrix{
    if (this->get_col_count() != right.get_row_count()) throw std::logic_error("Left col count and right row count must be equal to perform a multiplication");
    Matrix product(this->get_row_count(), right.get_col_count());
    for (size_type row = 0; row != get_row_count(); row++)
        for (size_type col = 0; col != right.get_col_count(); col++){
            row_type& row_container = get_row_container(row);
            col_type& col_container = right.get_col_container(col);
            value_ptr local_product = product.ptrAt(row, col);
            value_ptr new_product = std::inner_product(row_container.begin(), row_container.end(), col_container.begin(),
                                                       local_product, mat_value_sum<T, Container, Alloc>, mat_value_prod<T, Container, Alloc>);
            *local_product = *new_product;
        }


    return product;

}









