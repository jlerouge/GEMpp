#ifndef GEMPP_WEIGHTHASH_H
#define GEMPP_WEIGHTHASH_H

#include <QHash>
#include "Weight.h"

#define GEMPP_DEFAULT_MODE ADD
#define GEMPP_DEFAULT_ROOT 1

class DLL_EXPORT WeightHash : virtual public QHash<QString, Weight *> {
    public:
        enum Mode{
            ADD = 0,
            MULTIPLY,
            COUNT
        };

        static const char* modeName[COUNT];
        static Mode fromName(QString name);
        static QString toName(Mode mode);

        WeightHash(Mode mode = GEMPP_DEFAULT_MODE, uint root = GEMPP_DEFAULT_ROOT);
        ~WeightHash();

        Mode getMode() const;
        void setMode(Mode mode);
        uint getRoot() const;
        void setRoot(uint root);

    private:
        Mode mode_;
        uint root_;
};

#endif /* GEMPP_WEIGHTHASH_H */
