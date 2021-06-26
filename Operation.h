//
// Created by BedTed on 6/26/2021.
//

#ifndef OPZ_OPERATION_H
#define OPZ_OPERATION_H


class AOperation {
public:
    unsigned int priority;
    char operationSymbol;
    virtual int operation (int a, int b) = 0;
};

class plusOperation : public AOperation{

    virtual int operation (int a, int b) {
        return a + b;
    }
};

class subOperation : public AOperation {
    virtual int operation (int a, int b) {
        return a - b;
    }
};

class mulOperation : public AOperation {
    virtual int operation (int a, int b) {
        return a * b;
    }
};

class divOperation : public AOperation {
    virtual int operation (int a, int b) {
        return a / b;
    }
};

class leftBracet : public AOperation {

};




#endif //OPZ_OPERATION_H
