#pragma once
#include <QtWidgets/QAbstractScrollArea>

// Based on https://stackoverflow.com/questions/46375673/how-can-realize-my-own-memory-viewer-by-qt

class MemoryViewWidget : public QAbstractScrollArea
{
public:
  Q_OBJECT
public:
  MemoryViewWidget(QWidget* parent = nullptr, size_t address_offset = 0, void* data_ptr = nullptr, size_t data_size = 0,
                   bool data_editable = false);
  ~MemoryViewWidget();

  size_t addressOffset() const { return m_address_offset; }

  void setData(size_t address_offset, void* data_ptr, size_t data_size, bool data_editable);
  void setHighlightRange(size_t start, size_t end);
  void clearHighlightRange();
  void scrolltoOffset(size_t offset);
  void scrollToAddress(size_t address);
  void setFont(const QFont& font);

protected:
  void paintEvent(QPaintEvent* event);
  void resizeEvent(QResizeEvent* event);
  void mousePressEvent(QMouseEvent* event);
  void mouseMoveEvent(QMouseEvent* event);
  void keyPressEvent(QKeyEvent* event);

private Q_SLOTS:
  void adjustContent();

private:
  static constexpr size_t INVALID_SELECTED_ADDRESS = ~static_cast<size_t>(0);

  int addressWidth() const;
  int hexWidth() const;
  int asciiWidth() const;
  void updateMetrics();
  void updateSelectedByte(const QPoint& pos);

  void* m_data;
  size_t m_data_size;
  size_t m_address_offset;

  size_t m_start_offset;
  size_t m_end_offset;

  size_t m_highlight_start = 0;
  size_t m_highlight_end = 0;

  size_t m_selected_address = INVALID_SELECTED_ADDRESS;
  int m_editing_nibble = -1;
  bool m_selection_was_ascii = false;
  bool m_data_editable = false;

  unsigned m_bytes_per_line;

  int m_char_width;
  int m_char_height;

  int m_rows_visible;
};