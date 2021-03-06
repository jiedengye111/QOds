/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_ROW_HPP_
#define ODS_ROW_HPP_

#include "cell.hxx"
#include "err.hpp"
#include "global.hxx"
#include <QVector>

class QXmlStreamWriter;

namespace ods	{
class Cell;
class Sheet;
class Style;
class Tag;

class ODS_API Row
{
public:
	Row(ods::Sheet *sheet, ods::Tag*, const qint32 row_start);
	virtual ~Row();
	
	void
	Add(ods::Cell *cell) { cells_.push_back(cell); }
	
	void
	AddColCount(ods::Cell *cell);
	
	void
	AdjustHeightBy(ods::Cell *cell);
	
	ods::Cell*
	cell(const qint32 column);
	
	QVector<ods::Cell*>&
	cells() { return cells_; }
	
	qint32
	column_count() const { return column_count_; }
	
	void // called from Cell ctor
	column_count_set(const qint32 n) { column_count_ = n; }
	
	ods::Cell* //@@@HasDoc
	CreateCell(const qint32 at_column);
	
	ods::Cell*
	GetPrevCell(const qint32 at_column);
	
	void
	InitEnd();
	
	bool
	IsEmpty() const { return cells_.size() == 0; }
	
	qint32
	num_rows_repeated() const { return num_rows_repeated_; }
	
	void
	PreSave(const qint32 total_cols);
	
	qint32
	row_start() { return row_start_; }
	
	void
	row_start_set(const qint32 n) { row_start_ = n; }
	
	void
	SetCoveredCellRange(ods::Cell *cell, const qint32 col_start,
		const qint32 col_end);
	
	void
	SetNumRowsRepeated(const qint32 num);
	
	void
	SetOptimalHeightStyle();
	
	void
	SetStyle(ods::Style *style);
	
	ods::Sheet*
	sheet() { return sheet_; }
	
	ods::Tag*
	tag() { return tag_; }
	
	void
	UpdateColIndices();
	
	qint32
	UpToRow() const { return row_start_ + num_rows_repeated_ - 1; }
	
private:
	NO_ASSIGN_COPY_MOVE(Row);
	
	ods::Cell*
	GenCell(const qint32 at_column, const bool covered);
	
	void
	Init();
	
	ods::Cell*
	InsertCell(const qint32 column, const bool covered = false);
	
	ods::Cell*
	InsertEmptyCell(const qint32 at_column, const quint16 num_cols_repeated,
		const bool covered);
	
	QVector<ods::Cell*>	cells_;
	qint32			column_count_ = 0;
	qint32			num_rows_repeated_ = 1;
	ods::Style		*opt_row_height_style_ = nullptr;
	qint32			row_start_ = -1; // zero based
	ods::Sheet		*sheet_ = nullptr;
	QString			style_name_;
	ods::Tag		*tag_ = nullptr;
};

} // namespace ods
#endif
