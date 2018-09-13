#ifndef SKIN_H
#define SKIN_H

#include <QDialog>
#include "skinlabel.h"
class Skin : public QDialog
{
    Q_OBJECT
public:
    explicit Skin(QWidget *parent = nullptr);

    SkinLabel *skinLabel() const;
    void setSkinLabel(SkinLabel *skinLabel);

signals:

public slots:

private:
    SkinLabel *m_skinLabel;

protected:
    bool event(QEvent *event);
};

#endif // SKIN_H
