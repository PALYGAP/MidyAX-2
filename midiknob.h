#ifndef MIDIKNOB_H
#define MIDIKNOB_H


class MIDIKnob : public QObject
{
    Q_OBJECT
public:
    explicit MIDIKnob(QObject *parent = 0);

    QComboBox *m_TheComboBox;
    QLineEditMod1 *m_TheLineEdit;
    QList *m_TheBlockLabel;
    QList *m_TheParamLabel;
    QList *m_TheSlider;

signals:

public slots:
    void setBlockLabel( Qstring text );
    void setEffectLabel( Qstring text );
    void clearComboBox();
    void addComboBoxItem( QString, int index );
    void setComboBoxCurrentIndex( selectedPos );

private slots:
    void onSliderValueChanged( int value );
    void onComboBoxCurrentIndexChanged( int index );
    void onVerticalSliderCustomContextMenuRequested( const QPoint );

signals:
     void knobValueChanges(int value);
     void knobCBCurrentIndexChanged(int index);
     void knobCustomContextMenuRequested( QPoint loc );

};

#endif // MIDIKNOB_H
