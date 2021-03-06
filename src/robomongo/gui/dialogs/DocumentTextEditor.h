#pragma once

#include <QWidget>
#include <QDialog>
#include <mongo/client/dbclient.h>

namespace Robomongo
{
    class RoboScintilla;

    class DocumentTextEditor : public QDialog
    {
        Q_OBJECT

    public:
        explicit DocumentTextEditor(const QString &server, const QString &database, const QString &collection,
                                    const QString &json, bool readonly = false, QWidget *parent = 0);

        QString jsonText() const;

        /**
         * @brief Use returned BSONObj only if Dialog exec() method returns QDialog::Accepted
         */
        mongo::BSONObj bsonObj() const { return _obj; }

        void setCursorPosition(int line, int column);

    public slots:
        virtual void accept();
        bool validate(bool silentOnSuccess = true);

    private slots:
        void onQueryTextChanged();
        void onValidateButtonClicked();

    private:
        void _configureQueryText();
        QFont chooseTextFont();
        RoboScintilla *_queryText;
        QFont _textFont;
        bool _readonly;
        mongo::BSONObj _obj;
    };
}

