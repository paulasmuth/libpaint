/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2014 Paul Asmuth, Google Inc.
 *   Copyright (c) 2016 Paul Asmuth, FnordCorp B.V. <paul@asmuth.com>
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#pragma once
#include <atomic>
#include <memory>
#include <string>
#include "metricd/metric_map.h"
#include "metricd/metric.h"
#include "metricd/util/return_code.h"

namespace fnordmetric {
class MetricListCursor;
class MetricSeriesListCursor;
class MetricCursor;

class MetricService {
public:

  MetricService(std::shared_ptr<MetricMap> metric_map);

  /**
   * List all metrics
   */
  MetricListCursor listMetrics();

  /**
   * List all series in a metric
   */
  MetricSeriesListCursor listMetricsSeries(const MetricIDType& metric_id);

  /**
   * Insert a sample into a metric series
   */
  ReturnCode insertSample(
      const MetricIDType& metric_id,
      const LabelledSample& sample);

  /**
   * Get a cursor to a metric series
   */
  MetricCursor getCursor(
      const MetricIDType& metric_id,
      SeriesIDType series_id);

  /**
   * Return all samples from a metric series and time range
   */
  void scanSamples(
      const MetricIDType& metric_id,
      SeriesIDType series_id,
      TimestampType time_begin,
      TimestampType time_end,
      std::function<void (const Sample& sample)> foreach);

  /**
   * Get the most recent sample from a metric series
   */
  bool getMostRecentSample(
      const MetricIDType& metric_id,
      SeriesIDType series_id,
      Sample* sample);

protected:
  VersionedMetricMap metric_map_;
  SeriesIDProvider id_provider_;
  //tsdb::TSDB tsdb_;
};

} // namespace fnordmetric
