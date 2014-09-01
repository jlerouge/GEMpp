#ifndef __WEIGHTHASH_H__
#define __WEIGHTHASH_H__

#include <QHash>
#include "Weight.h"

#define DEFAULT_MODE ADD
#define DEFAULT_ROOT 1

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

        WeightHash(Mode mode = DEFAULT_MODE, uint root = DEFAULT_ROOT);
        ~WeightHash();

        Mode getMode() const;
        void setMode(Mode mode);
        uint getRoot() const;
        void setRoot(uint root);

    private:
        Mode mode_;
        uint root_;
};

#endif /*__WEIGHTS_H__*/
