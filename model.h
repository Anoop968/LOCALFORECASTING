#pragma once
#include <cstdarg>
#include <cmath> // IMPORTANT: This is needed for percentage math

namespace Eloquent {
    namespace ML {
        namespace Port {
            class LogisticRegression {
                public:
                    /**
                    * Predict class (0 or 1)
                    */
                    int predict(float *x) {
                        float score = calculateScore(x);
                        return (score > 0) ? 0 : 1; // If score is positive, it's 'No Rain'
                    }

                    /**
                    * Predict readable name
                    */
                    const char* predictLabel(float *x) {
                        return (predict(x) == 0) ? "No Rain" : "Rain";
                    }

                    /**
                    * THE MISSING FUNCTION: Predict Percentage
                    */
                    void predictProbabilities(float *x, float *probabilities) {
                        float score = calculateScore(x);
                        
                        // Sigmoid Math: 1 / (1 + e^-score)
                        // This gives the probability of 'No Rain' (Class 0)
                        float p0 = 1.0 / (1.0 + exp(-score));
                        
                        probabilities[0] = p0;        // No Rain %
                        probabilities[1] = 1.0 - p0;  // Rain %
                    }

                protected:
                    /**
                    * Helper to calculate the raw weighted sum
                    */
                    float calculateScore(float *x) {
                        // These are the weights from your specific training session
                        float score = 0.425460240405;       // Bias
                        score += x[0] * -0.024452676732;    // Temperature Weight
                        score += x[1] * 0.004033816153;     // Humidity Weight
                        return score;
                    }
            };
        }
    }
}