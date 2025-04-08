#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "list/XArrayList.h"
#include "list/DLinkedList.h"
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

// -------------------- List1D --------------------
template <typename T>
class List1D
{
private:
    IList<T> *pList;

public:
    List1D();
    List1D(int num_elements);
    List1D(const T *array, int num_elements);
    List1D(const List1D<T> &other);
    virtual ~List1D();

    int size() const;
    T get(int index) const;
    void set(int index, T value);
    void add(const T &value);
    string toString() const;

    List1D<T> &operator=(const List1D<T> &other); // additional
    void addAtIndex(int index ,const T &value); // additional
    void removeAtIndex (int index); // additional

    template <typename U>
    friend ostream &operator<<(ostream &os, const List1D<T> &list);
};

// -------------------- List2D --------------------
template <typename T>
class List2D
{
private:
    IList<IList<T> *> *pMatrix;

public:
    List2D();
    List2D(List1D<T> *array, int num_rows);
    List2D(const List2D<T> &other);
    virtual ~List2D();

    int rows() const;
    void setRow(int rowIndex, const List1D<T> &row);
    T get(int rowIndex, int colIndex) const;
    List1D<T> getRow(int rowIndex) const;
    string toString() const;

    List2D<T> &operator=(const List2D<T> &other); // additional
    void removeAtIndex(int index); // additional

    template <typename U>
    friend ostream &operator<<(ostream &os, const List2D<T> &matrix);
};

struct InventoryAttribute
{
    string name;
    double value;
    // additional
    InventoryAttribute() : name(""), value(0.0) {}  // default constructor
    InventoryAttribute(const string &name, double value) : name(name), value(value) {}
    string toString() const { return name + ": " + to_string(value); }
    // additional
    bool operator==(const InventoryAttribute& other) const 
    {
        return name == other.name && value == other.value;
    }
    friend std::ostream &operator<<(std::ostream &os, const InventoryAttribute &attr) 
    {
        return os << attr.toString();
    }
};

// -------------------- InventoryManager --------------------
class InventoryManager
{
private:
    List2D<InventoryAttribute> attributesMatrix;
    List1D<string> productNames;
    List1D<int> quantities;

public:
    InventoryManager();
    InventoryManager(const List2D<InventoryAttribute> &matrix,
                     const List1D<string> &names,
                     const List1D<int> &quantities);
    InventoryManager(const InventoryManager &other);

    int size() const;
    List1D<InventoryAttribute> getProductAttributes(int index) const;
    string getProductName(int index) const;
    int getProductQuantity(int index) const;
    void updateQuantity(int index, int newQuantity);
    void addProduct(const List1D<InventoryAttribute> &attributes, const string &name, int quantity);
    void removeProduct(int index);

    List1D<string> query(string attributeName, const double &minValue,
                         const double &maxValue, int minQuantity, bool ascending) const;

    void removeDuplicates();

    static InventoryManager merge(const InventoryManager &inv1,
                                  const InventoryManager &inv2);

    void split(InventoryManager &section1,
               InventoryManager &section2,
               double ratio) const;

    List2D<InventoryAttribute> getAttributesMatrix() const;
    List1D<string> getProductNames() const;
    List1D<int> getQuantities() const;
    string toString() const;
};

// -------------------- List1D Method Definitions --------------------
template <typename T>
List1D<T>::List1D()
{
    // TODO
    pList = new XArrayList<T>();
}

template <typename T>
List1D<T>::List1D(int num_elements)
{
    // TODO
    pList = new XArrayList<T>();
    for (int i = 0; i < num_elements; i++)
    {
        pList->add(T());
    }
}

template <typename T>
List1D<T>::List1D(const T *array, int num_elements)
{
    // TODO
    pList = new XArrayList<T>();
    for (int i = 0; i < num_elements; i++)
    {
        pList->add(array[i]);
    }
}

template <typename T>
List1D<T>::List1D(const List1D<T> &other)
{
    // TODO
    pList = new XArrayList<T>();
    for (int i = 0; i < other.size(); i++)
    {
        pList->add(other.get(i));
    }
}

template <typename T>
List1D<T>::~List1D()
{
    // TODO
    delete pList;
}

template <typename T>
int List1D<T>::size() const
{
    // TODO
    return pList->size();
}

template <typename T>
T List1D<T>::get(int index) const
{
    // TODO
    return pList->get(index);
}

template <typename T>
void List1D<T>::set(int index, T value)
{
    // TODO
    if (index < 0 || index > pList->size()) throw std::out_of_range("Index is out of range!");
    if (index == pList->size()) // xem nhu add cuoi
    {
        pList->add(value);
        return;
    }
    pList->removeAt(index);
    pList->add(index, value);
}

template <typename T>
void List1D<T>::add(const T &value)
{
    // TODO
    pList->add(value);
}

template <typename T>
void List1D<T>::addAtIndex(int index,const T &value) // additional
{
    // TODO
    pList->add(index, value);
}

template <typename T>
string List1D<T>::toString() const
{
    // TODO
    stringstream ss;
    ss << "[";
    for (int i = 0; i < pList->size(); i++) 
    {
        ss << pList->get(i);
        if (i < pList->size() - 1) 
        {
            ss << ", ";
        }
    }
    ss << "]";
    return ss.str(); // [e1, e2, ..., en]
}

template<typename T>
void List1D<T>::removeAtIndex(int index)
{
    pList->removeAt(index);
}

template <typename T>
List1D<T> &List1D<T>::operator=(const List1D<T> &other)
{
    if (this != &other)
    {
        delete pList;
        pList = new XArrayList<T>();
        for (int i = 0; i < other.size(); i++)
        {
            pList->add(other.get(i));
        }
    }
    return *this;
}

template <typename T>
ostream &operator<<(ostream &os, const List1D<T> &list)
{
    // TODO
    os << list.toString();
    return os;
}

// -------------------- List2D Method Definitions --------------------
template <typename T>
List2D<T>::List2D()
{
    // TODO
    pMatrix = new XArrayList<IList<T> *>();
}

template <typename T>
List2D<T>::List2D(List1D<T> *array, int num_rows)
{
    // TODO
    pMatrix = new XArrayList<IList<T> *>();
    for (int i = 0; i < num_rows; i++) 
    {
        IList<T> *newRow = new XArrayList<T>(); 
        for (int j = 0; j < array[i].size(); j++) 
        {
            newRow->add(array[i].get(j));
        }
        pMatrix->add(newRow);
    }
}

template <typename T>
List2D<T> &List2D<T>::operator=(const List2D<T> &other)
{
    if (this != &other) 
    {
        for (int i = 0; i < pMatrix->size(); i++)
        {
            delete pMatrix->get(i);
        }
        delete pMatrix; 

        pMatrix = new XArrayList<IList<T> *>();
        for (int i = 0; i < other.rows(); i++)
        {
            List1D<T> row = other.getRow(i); 
            IList<T> *newRow = new XArrayList<T>(); 
            for (int j = 0; j < row.size(); j++)
            {
                newRow->add(row.get(j)); 
            }
            pMatrix->add(newRow); 
        }
    }
    return *this; 
}

template <typename T>
List2D<T>::List2D(const List2D<T> &other)
{
    // TODO
    pMatrix = new XArrayList<IList<T> *>();
    for (int i = 0; i < other.rows(); i++) 
    {
        List1D<T> row = other.getRow(i);
        IList<T> *newRow = new XArrayList<T>();
        for (int j = 0; j < row.size(); j++) 
        {
            newRow->add(row.get(j));
        }
        pMatrix->add(newRow);
    }
}

template <typename T>
List2D<T>::~List2D()
{
    // TODO
    for (int i = 0; i < pMatrix->size(); i++)
    {
        delete pMatrix->get(i);
    }
    delete pMatrix;
}

template <typename T>
int List2D<T>::rows() const // dem so hang cua ma tran
{
    // TODO
    return pMatrix->size();
}

template <typename T>
void List2D<T>::setRow(int rowIndex, const List1D<T> &row)
{
    // TODO
    if (rowIndex < 0 || rowIndex > pMatrix->size()) throw out_of_range("Index is out of range!");
    if (rowIndex == pMatrix->size()) 
    {
        IList<T> *newRow = new XArrayList<T>();
        for (int j = 0; j < row.size(); j++) 
        {
            newRow->add(row.get(j));
        }
        pMatrix->add(newRow);
    } 
    else 
    {
        delete pMatrix->get(rowIndex); 
        pMatrix->removeAt(rowIndex);
        IList<T> *newRow = new XArrayList<T>();
        for (int j = 0; j < row.size(); j++) 
        {
            newRow->add(row.get(j));
        }
        pMatrix->add(rowIndex, newRow); 
    }
}

template <typename T>
void List2D<T>::removeAtIndex(int index)
{
    if (index < 0 || index >= pMatrix->size()) throw std::out_of_range("Index is out of range!");
    delete pMatrix->get(index);
    pMatrix->removeAt(index);
}

template <typename T>
T List2D<T>::get(int rowIndex, int colIndex) const // lay ra phan tu (i, j) cua ma tran
{
    // TODO
    if (rowIndex < 0 || rowIndex >= pMatrix->size()) throw out_of_range("Index is out of range!");
    IList<T> *row = pMatrix->get(rowIndex);
    if (colIndex < 0 || colIndex >= row->size()) throw out_of_range("Index is out of range!");
    return row->get(colIndex);
}

template <typename T>
List1D<T> List2D<T>::getRow(int rowIndex) const // lay ra mot hang
{
    // TODO
    if (rowIndex < 0 || rowIndex >= pMatrix->size()) throw out_of_range("Index is out of range!");
    IList<T> *row = pMatrix->get(rowIndex);
    List1D<T> result(row->size());
    for (int j = 0; j < row->size(); j++) 
    {
        result.set(j, row->get(j));
    }
    return result;
}

template <typename T>
string List2D<T>::toString() const
{
    // TODO
    stringstream ss;
    ss << "[";
    for (int i = 0; i < pMatrix->size(); i++) 
    {
        ss << "[";
        for (int j = 0; j < pMatrix->get(i)->size(); j++) 
        {
            ss << pMatrix->get(i)->get(j);
            if (j < pMatrix->get(i)->size() - 1) ss << ", ";
        }
        ss << "]";
        if (i < pMatrix->size() - 1) ss << ", ";
    }
    ss << "]";
    return ss.str();
}

template <typename T>
ostream &operator<<(ostream &os, const List2D<T> &matrix)
{
    // TODO
    os << matrix.toString();
    return os;
}

// -------------------- InventoryManager Method Definitions --------------------
InventoryManager::InventoryManager()
{
    // TODO
    attributesMatrix = List2D<InventoryAttribute>(); 
    productNames = List1D<string>();                 
    quantities = List1D<int>();
}

InventoryManager::InventoryManager(const List2D<InventoryAttribute> &matrix,
                                   const List1D<string> &names,
                                   const List1D<int> &quantities) : attributesMatrix(matrix), productNames(names), quantities(quantities) {}

InventoryManager::InventoryManager(const InventoryManager &other)
: attributesMatrix(other.attributesMatrix), productNames(other.productNames), quantities(other.quantities) {}

int InventoryManager::size() const
{
    // TODO
    return productNames.size();
}

List1D<InventoryAttribute> InventoryManager::getProductAttributes(int index) const
{
    // TODO
    if (index < 0 || index >= size()) throw std::out_of_range("Index is invalid!");
    return attributesMatrix.getRow(index);
}

string InventoryManager::getProductName(int index) const
{
    // TODO
    if (index < 0 || index >= size()) throw std::out_of_range("Index is invalid!");
    return productNames.get(index);
}

int InventoryManager::getProductQuantity(int index) const
{
    // TODO
    if (index < 0 || index >= size()) throw std::out_of_range("Index is invalid!");
    return quantities.get(index);
}

void InventoryManager::updateQuantity(int index, int newQuantity)
{
    // TODO
    if (index < 0 || index >= size()) throw std::out_of_range("Index is invalid!");
    quantities.set(index, newQuantity);
}

void InventoryManager::addProduct(const List1D<InventoryAttribute> &attributes, const string &name, int quantity)
{
    // TODO
    attributesMatrix.setRow(attributesMatrix.rows(), attributes);
    productNames.add(name);
    quantities.add(quantity);
}

void InventoryManager::removeProduct(int index)
{
    // TODO
    if (index < 0 || index >= size()) throw std::out_of_range("Index is invalid!");
    attributesMatrix.removeAtIndex(index);
    productNames.removeAtIndex(index);
    quantities.removeAtIndex(index);
}

List1D<string> InventoryManager::query(string attributeName, const double &minValue,
                                       const double &maxValue, int minQuantity, bool ascending) const
{
    // TODO
    List1D<string> nameList;   // Ds luu ten
    List1D<double> valueList;  // Ds luu gia tri thuoc tinh
    List1D<int> indexList;     // Ds luu index goc
    List1D<int> quantityList;  // Ds luu so luong
    // Loc sp
    for (int i = 0; i < size(); i++)
    {
        List1D<InventoryAttribute> atb = getProductAttributes(i);
        int qty = getProductQuantity(i);
        bool found = false;
        double val = 0.0;
        for (int j = 0; j < atb.size(); j++)
        {
            if (atb.get(j).name == attributeName)
            {
                found = true;
                val = atb.get(j).value;
                break;
            }
        }

        if (found && val >= minValue && val <= maxValue && qty >= minQuantity)
        {   // luu vao cac ds
            nameList.add(getProductName(i));
            valueList.add(val);
            // indexList.add(i % productNames.size()); 
            indexList.add(i);
            quantityList.add(qty);
        }
    }
    // Ds chi so de sap xep
    List1D<int> order;
    for (int i = 0; i < nameList.size(); i++)
    {
        order.add(i);
    }
    
    for (int i = 0; i < order.size(); i++) // sap xep bubble sort
    {
        for (int j = i + 1; j < order.size(); j++)
        {
            int idx_i = order.get(i);
            int idx_j = order.get(j);
            bool shouldSwap;
            if (ascending)
            {
                // valueList tang dan
                // neu valueList = nhau, quantityList tang dan
                // neu quantityList = nhau, indexList tang dan
                shouldSwap = (valueList.get(idx_i) > valueList.get(idx_j)) ||
                             (valueList.get(idx_i) == valueList.get(idx_j) &&
                              quantityList.get(idx_i) > quantityList.get(idx_j)) ||
                             (valueList.get(idx_i) == valueList.get(idx_j) &&
                              quantityList.get(idx_i) == quantityList.get(idx_j) &&
                              indexList.get(idx_i) > indexList.get(idx_j));
            }
            else
            {
                // valueList giam dan
                // neu valueList = nhau, quantityList giam dan
                // neu quantityList = nhau, indexList tang dan
                shouldSwap = (valueList.get(idx_i) < valueList.get(idx_j)) ||
                             (valueList.get(idx_i) == valueList.get(idx_j) &&
                              quantityList.get(idx_i) < quantityList.get(idx_j)) ||
                             (valueList.get(idx_i) == valueList.get(idx_j) &&
                              quantityList.get(idx_i) == quantityList.get(idx_j) &&
                              indexList.get(idx_i) < indexList.get(idx_j));
            }
            if (shouldSwap) // neu shouldSwap = false thi ko can sap xep, vi sp da o dung vi tri 
            {
                int temp = order.get(i);
                order.set(i, order.get(j));
                order.set(j, temp);
            }
        }
    }
    List1D<string> res;
    for (int i = 0; i < order.size(); i++)
    {
        int idx = order.get(i);
        res.add(nameList.get(idx));
    }
    return res;
}

void InventoryManager::removeDuplicates()
{
    // TODO
    // duyet tung sp
    for (int i = 0; i < size() - 1; i++)
    {   // cac thuoc tinh san pham i
        List1D<InventoryAttribute> atb_i = getProductAttributes(i);
        string name_i = getProductName(i);
        int totalQty = getProductQuantity(i);
        
        for (int j = size() - 1; j > i; j--) // so sanh vs cac san pham phia sau
        {
            List1D<InventoryAttribute> atb_j = getProductAttributes(j);
            string name_j = getProductName(j);
            if (name_i == name_j && atb_i.toString() == atb_j.toString()) // kiem tra cung ten va cung dach sach thuoc tinh
            {
                totalQty += getProductQuantity(j); // cong don so luong
                removeProduct(j);              // xoa san pham trung
            }
        }
        updateQuantity(i, totalQty); // cap nhap lai so luong sp i
    }
}

InventoryManager InventoryManager::merge(const InventoryManager &inv1,
                                         const InventoryManager &inv2)
{
    // TODO
    InventoryManager res;
    for (int i = 0; i < inv1.size(); i++)
    {
        res.addProduct(inv1.getProductAttributes(i), inv1.getProductName(i), inv1.getProductQuantity(i));
    }
    for (int i = 0; i < inv2.size(); i++)
    {
        res.addProduct(inv2.getProductAttributes(i), inv2.getProductName(i), inv2.getProductQuantity(i));
    }
    return res;
}

void InventoryManager::split(InventoryManager &section1,
                             InventoryManager &section2,
                             double ratio) const
{
    // TODO
    // phai xoa du lieu cua s1 & s2, neu khong cac lan goi tiep theo se bi sai
    while (section1.size() > 0)
    {
        section1.removeProduct(0);
    }
    while (section2.size() > 0)
    {
        section2.removeProduct(0);
    }
    double adjustedRatio = ratio;
    if (ratio < 0) adjustedRatio = 0; // section1 rong, section2 nhan het
    if (ratio > 1) adjustedRatio = 1; // section1 nhan het, section2 rong

    // tinh so luong sp cua s1 va lam tron len
    int productCounts = size();
    int section1_size = (int)(productCounts * adjustedRatio + 0.999);
    // section1_size = max(0, min(section1_size, productCounts)); // dam bao size cua s1 luon nam trong [0, size()]

    // add sp vao s1
    for (int i = 0; i < section1_size; i++)
    {
        section1.addProduct(getProductAttributes(i), getProductName(i), getProductQuantity(i));
    }
    // add sp con lai vao s2
    for (int i = section1_size; i < productCounts; i++)
    {
        section2.addProduct(getProductAttributes(i), getProductName(i), getProductQuantity(i));
    }
}

List2D<InventoryAttribute> InventoryManager::getAttributesMatrix() const
{
    // TODO
    return attributesMatrix;
}

List1D<string> InventoryManager::getProductNames() const
{
    // TODO
    return productNames;
}

List1D<int> InventoryManager::getQuantities() const
{
    // TODO
    return quantities;
}

string InventoryManager::toString() const
{
    // TODO
    stringstream ss;
    ss << "InventoryManager[\n";
    ss << "  AttributesMatrix: " << attributesMatrix.toString() << ",\n";
    ss << "  ProductNames: " << productNames.toString() << ",\n";
    ss << "  Quantities: " << quantities.toString() << "\n";
    ss << "]";
    return ss.str();
}

#endif /* INVENTORY_MANAGER_H */
