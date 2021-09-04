# Problems

## 1-1 Comparison of running times

For each function *f*(*n*) and time *t* in the following table, determine the largest size *n* of a problem that can be solved in time *t*, assuming that the algorithm to solve the problem takes *f*(*n*) microseconds.

| |1<br>second|1<br>minute|1<br>hour|1<br>day|1<br>month|1<br>year|1<br>century|
|---|---|---|---|---|---|---|---|
|*log n*|2<sup>1000000</sup>|2<sup>6 × 10<sup>7</sup></sup>|2<sup>3.6 × 10<sup>9</sup></sup>|2<sup>8.64 × 10<sup>10</sup></sup>|2<sup>2.628 × 10<sup>12</sup></sup>|2<sup>3.154 × 10<sup>13</sup></sup>|2<sup>3.154 × 10<sup>15</sup></sup>|
|√*n*|10<sup>12</sup>|(6 × 10<sup>7</sup>)<sup>2</sup>|(3.6 × 10<sup>9</sup>)<sup>2</sup>|(8.64 × 10<sup>10</sup>)<sup>2</sup>|(2.628 × 10<sup>12</sup>)<sup>2</sup>|(3.154 × 10<sup>13</sup>)<sup>2</sup>|(3.154 × 10<sup>15</sup>)<sup>2</sup>|
|*n*|10<sup>7</sup>|6 × 10<sup>7</sup>|3.6 × 10<sup>9</sup>|8.64 × 10<sup>10</sup>|2.628 × 10<sup>12</sup>|3.154 × 10<sup>13</sup>|3.154 × 10<sup>15</sup>|
|*n log n*|62746|2.80142×10<sup>6</sup>|1.33378×10<sup>8</sup>|2.75515×10<sup>9</sup>|7.28304×10<sup>10</sup>|7.97732 × 10<sup>11</sup>|6.86194×10<sup>13</sup>|
|*n*<sup>2</sup>|3162|7745|60000|293938|(2.628 × 10<sup>12</sup>)<sup>1/2</sup>|(3.154 × 10<sup>13</sup>)<sup>1/2</sup>|(3.154 × 10<sup>15</sup>)<sup>1/2</sup>|
|*n*<sup>3</sup>|(10<sup>7</sup>)<sup>1/3</sup>|(6 × 10<sup>7</sup>)<sup>1/3</sup>|(3.6 × 10<sup>9</sup>)<sup>1/3</sup>|(8.64 × 10<sup>10</sup>)<sup>1/3</sup>|(2.628 × 10<sup>12</sup>)<sup>1/3</sup>|(3.154 × 10<sup>13</sup>)<sup>1/3</sup>|(3.154 × 10<sup>15</sup>)<sup>1/3</sup>|
|2<sup>*n*</sup>|19|25|31|36|41|44|51|
|*n*!|9|11|12|13|15|16|17|