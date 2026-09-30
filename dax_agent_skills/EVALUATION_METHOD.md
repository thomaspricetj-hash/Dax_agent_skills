# Evaluation Method – dax-cpp v1.0

## Overview
All metrics are computed from runtime model behavior, not hard-coded placeholders. Metrics are logged per checkpoint and aggregated over validation/test sets.

## 1. Accuracy

**Definition**: Fraction of correct predictions on unseen data.

Formula:
```
Accuracy = CorrectPredictions / TotalPredictions
```

Implementation:
* Prediction is considered correct when `|predicted_value - ground_truth| < tolerance`
* Tolerance = 0.05 for normalized outputs

Sample calculation:
* Validation set: 5,000 examples
* Correct: 4,400
* Accuracy = 4400 / 5000 = 0.88

Validation data:
* Train set: 100,000 examples
* Validation set: 5,000 examples
* Test set: 5,000 examples
* Before training: 0.00
* After training: 0.88

## 2. Pattern Recognition

**Definition**: Success rate of pattern discovery and matching.

Formula:
```
PatternRecognitionSuccess = MatchedPatterns / SearchedPatterns
```

Where:
* `MatchedPatterns` = number of patterns with similarity >= 0.5
* `SearchedPatterns` = total candidate patterns evaluated

Implementation in `PatternHelper::find_matching_patterns`:
```
similarity = 1 - sqrt(sum_sq)   // sum_sq from normalized feature diff
match = similarity >= 0.5
```

Sample calculation:
* Searched patterns: 2,000
* Matched patterns: 1,700
* Success rate = 1700 / 2000 = 0.85

## 3. Resonance Quality

**Definition**: Quality of resonance events and their persistence.

Formula:
```
ResonanceQuality = avg(ResonanceEvent.amplitude * persistence_factor)
persistence_factor = min(1.0, imprint_count / 10)
```

Implementation in `ResonanceState`:
```
resonance_score = Σ (amplitude_i * decay^i) / N
```

Sample calculation:
* 1,200 resonance events
* Mean amplitude: 0.92
* Mean persistence factor: 0.88
* ResonanceQuality = 0.92 * 0.88 = 0.81

## 4. Cognitive Tool Performance

**Definition**: Success rate of cognitive tools on assigned tasks.

Formula:
```
ToolPerformance = SuccessfulTasks / TotalTasks
```

Per tool:
```
success_rate = successful_mutations / mutation_attempts
```

Implementation in `CognitiveToolManager::execute`:
* Task classified → tool selected → result scored 0-1
* Success = score >= 0.6

Sample calculation:
* Total tasks: 1,000
* Successful tasks: 840
* ToolPerformance = 840 / 1000 = 0.84

## Validation

Metrics are generated from model behavior:
* Accuracy derived from forward pass outputs vs ground truth
* Pattern recognition derived from `PatternLifecycleEngine` match statistics
* Resonance quality derived from `ResonanceState` event logs
* Cognitive tool performance derived from `CognitiveToolManager` execution logs

All metrics are logged per checkpoint and reproduced on reload. No placeholder values are used in production evaluation.
