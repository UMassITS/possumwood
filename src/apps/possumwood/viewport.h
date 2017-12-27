#pragma once

#include <vector>
#include <memory>

#include <boost/noncopyable.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <GL/glew.h>
#include <GL/gl.h>

#include <QtOpenGL/QGLWidget>

#include <ImathVec.h>
#include <ImathMatrix.h>

#include "grid.h"

class Viewport : public QGLWidget, public boost::noncopyable {
	Q_OBJECT

  signals:
	void render(float dt);

  public:
	Viewport(QWidget* parent = NULL);
	virtual ~Viewport();

	const Imath::M44f& projection() const;
	const Imath::M44f& modelview() const;

  protected:
	virtual void initializeGL();
	virtual void paintGL();
	virtual void resizeGL(int w, int h);
	virtual void mouseMoveEvent(QMouseEvent* event);

  private:
	float m_sceneDistance, m_sceneRotationX, m_sceneRotationY;
	Imath::V3f m_origin;
	int m_mouseX, m_mouseY;

	Imath::M44f m_projection, m_modelview;

	boost::posix_time::ptime m_timer;

	std::unique_ptr<possumwood::Grid> m_grid;
};
