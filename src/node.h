#pragma once

#include <string>

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>

#include "port.h"

class Node : public QGraphicsRectItem {
	public:
		Node(const QString& name, const QPointF& position = QPointF(0,0),
			const std::initializer_list< std::pair<QString, Port::Type> >& ports = std::initializer_list< std::pair<QString, Port::Type> >());

		void setName(const QString& n);
		const QString name() const;

	protected:
	private:
		void updateRect();

		QGraphicsRectItem* m_titleBackground;
		QGraphicsTextItem* m_title;
		QVector<Port*> m_ports;
};
