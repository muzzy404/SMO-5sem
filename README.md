# Queueing theory system project
__The coursework, SPbPU 5th semester__

__*Variant 3*__

| feature                     | type        | description                                                                         |
| --------------------------- | ----------- | ----------------------------------------------------------------------------------- |
| __*model*__                 |             |                                                                                     |
| producers/sources           | "endless"   | separate queries (not packages/sets)                                                |
| producers distribution rule | uniform     | [uniform distribution](https://en.wikipedia.org/wiki/Discrete_uniform_distribution) |
| service rule                | exponential | [exponential distribution](https://en.wikipedia.org/wiki/Exponential_distribution)  |
| __*enqueue*__               |                        |                                                                   |
| enqueue policy (buffering)  | first empty place      | query goes to first empty place in buffer                         |
| rejection policy            | in case of full buffer | query goes out of system - if there are no empty places in buffer |
| __*dequeue*__               |                                                             |                                      |
| consumer                    | selecton by priority (higher first)                         | consumer priority - its index number |
| query/request               | selecton by priority (higher first) and time (oldest first) | query priority - its producer priority, if few queries have the same priority - the oldest one will be selected |
| __*process/results*__       |                                   |   |
| automatic                   | summary results table             | - |
| step by step                | user sees each step of system job | - |


## Settings window
![Settings - step by step off](https://cldup.com/wlpqD9B0jH.png) ![Settings - step by step on](https://cldup.com/shudtFTzU7.png) 

| parameter(-s) |                                                     |
| ------------- | --------------------------------------------------- |
| *α and β*     | parameters of uniform distribution (α ≤ number ≤ β) |
| *λ*           | parameter of exponential distribution (1/λ is mean) |

## Simulation window
- If user set on the step by step mode - user will be pressing the Next button to move to the next step of system job.
- If user set off the step by step mode - user will be seeing the whole job of system at once.

![Simulation process](https://cldup.com/G7kQ3CjWD5.png)
![Simulation process done](https://cldup.com/hXcO2Nm3Kr.png)

## Results window
In the Results window, all the necessary system characteristics are displayed after the simulation is completed.
To open this window, click on the Results button in the Simulation window.

![Results](https://cldup.com/F9k2BpDhZg.png)

<p align="center">
  <i>Zelenova Daria 2017</i><br>
</p>
