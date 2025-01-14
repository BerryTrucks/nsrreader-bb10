#ifndef NSRACTIONAGGREGATOR_H_
#define NSRACTIONAGGREGATOR_H_

#include <bb/cascades/AbstractActionItem>

#include <QObject>
#include <QString>
#include <QHash>

class NSRActionAggregator : public QObject
{
	Q_OBJECT
public:
	NSRActionAggregator (QObject *parent = 0);
	virtual ~NSRActionAggregator ();

	void addAction (const QString& name, bb::cascades::AbstractActionItem *action);
	void setActionEnabled (const QString& name, bool enabled);
	bool isActionEnabled (const QString& name) const;
	bb::cascades::AbstractActionItem * removeAction (const QString& name);
	void clear ();
	void setAllEnabled (bool enabled);
	bb::cascades::AbstractActionItem * actionByName (const QString& name);

private:
	QHash < QString, bb::cascades::AbstractActionItem * >	_hash;
};

#endif /* NSRACTIONAGGREGATOR_H_ */
