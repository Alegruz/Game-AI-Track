# Exercises

## 1.12 How do clustered systems differ from multiprocessor systems? What is required for two machines belonging to a cluster to cooperate to provide a highly available service?

Multiprocessors operate in a single-core CPU computer system, while clustered systems operate as a collection of computer systems.

Clustered system needs to continue a service even if one or more sstems in the cluster fail. This is provided by increasing the level of redundancy in the system.

## 1.13 Consider a computing cluster consisting of two nodes running a database. Describe two ways in which the cluster software can manage access to the data on the disk. Discuss the benefits and disadvantages of each

1. Asymmetric. One machine runs the database while the other one is in hot-standby mode to monitor the active machine.
   * Benefit: Works rather as a single system, thus problems that arise in traditional clustered system. Running single application is available.
   * Disadvantages: Only single machine is running, so full capacity is lower than the number of total machines.
2. Symmetric. Both machines run the application and monitors each other
   * Benefit: More efficient as it uses all of the available hardware
   * Disadvantages: Requires more than one application be available to run

## 1.14 What is the purpose of interrupts? How does an interrupt differ from a trap? Can traps be generated intentionally by a user program? If so, for what purpose?

### Purpose

To let the controller inform the device driver that it has finished its operation.

### Trap

Trap is a software-generated interrupt caused either by an error or by a specific request from a user that an operating-system service be performed by executing a system call.

## 1.15 Explain how the Linux kernel variables HZ and jiffies can be used to determine the number of seconds the system has been running since it was booted

HZ specifies the frequency of timer interrupts. jiffies represents the number of timer interrupts that have occurred since the system was booted. So by dividing the jiffies by HZ results in the number of seconds the system has been running since it was booted.

## 1.16 Direct memory access is used for high-speed I/O devices in order to avoid increasing the CPU’s execution load

### a. How does the CPU interface with the device to coordinate the transfer?

### b. How does the CPU know when the memory operations are complete?

### c. The CPU is allowed to execute other programs while the DMA controller is transferring data. Does this process interfere with the execution of the user programs? If so, describe what forms of interference are caused

## 1.17 Some computer systems do not provide a privileged mode of operation in hardware. Is it possible to construct a secure operating system for these computer systems? Give arguments both that it is and that it is not possible

### Constructing a secure operationg system that do not provide a privileged mode of operation in hardware is possible

By restricting the accessibility of security to kernel mode, in other words, restricting the functionalities of the user to never interfere with the kernel mode, we can provide security.

### Constructing a secure operationg system that do not provide a privileged mode of operation in hardware is not possible

Operating system must be user friendly, thus systems without privileged mode of operations will greatly restrict the user's capabilities of communicating with other devices, especially I/O devices.

## 1.18 Many SMP systems have different levels of caches; one level is local to each processing core, and another level is shared among all processing cores. Why are caching systems designed this way?

Accessing a register/cache of another processor consumes more time. Thus sharing a bigger cache in-between individiual processors in a single chip solves this problem.

## 1.19 Rank the following storage systems from slowest to fastest

a. Hard-disk drives
b. Registers
c. Optical disk
d. Main memory
e. Nonvolatile memory
f. Magnetic tapes
g. Cache

1. Magnetic tapes
2. Optical disk
3. Hard-disk drives
4. Nonvolatile memory
5. Main memory
6. Cache
7. Registers

## 1.20 Consider an SMP system similar to the one shown in Figure 1.8. Illustrate with an example how data residing in memory could in fact have a different value in each of the local caches

If both processors access the same item in the main memory and perform different operations, each processor might have different modified item in their own register/cache.

## 1.21 Discuss, with examples, how the problem of maintaining coherence of cached data manifests itself in the following processing environments

### a. Single-processor systems

When multitasking, it must be ensured that if several processes wish to access an item, then each of these processes will obtain the most recent updated value of that item.

### b. Multiprocessor systems

A copy of an item may exist simultaneously in several caches. We must make sure that an update to the value of that item in one cache is immediately reflected in all other caches where that item resides.

### c. Distributed systems

Various replicas may be accessed and updated concurrently, we need to ensure that when a replica is updated in on place, all other replicas are brought up to date as soon as possible.

## 1.22 Describe a mechanism for enforcing memory protection in order to prevent a program from modifying the memory associated with other programs

Operating system should know which memories are being used, and who are using them. When some program tries to modify a memory owned by another program, then the operating should either produce a trap or ignore the command.

## 1.23 Which network configuration—LAN or WAN—would best suit the following environments?

### a. A campus student union

LAN

### b. Several campus locations across a statewide university system

WAN

### c. A neighborhood

LAN

## 1.24 Describe some of the challenges of designing operating systems for mobile devices compared with designing operating systems for traditional PCs

It needs to provide access to on-line services by IEEE standard 802.11 wireless or cellular data networks. It should also provide functionalities for GPS and accelerometer.

## 1.25 What are some advantages of peer-to-peer systems over client–server systems?

In client-server system, server is a bottleneck, but in a peer-to-peer system, services can be provided by several nodes distributed throughout the network

## 1.26 Describe some distributed applications that would be appropriate for a peer-to-peer system

VoIP. WebRTC.

## 1.27 Identify several advantages and several disadvantages of open-source operating systems. Identify the types of people who would find each aspect to be an advantage or a disadvantage

### Advantage

Students can find a decent source code to study. People looking for a job can use the repository as a form of portfolio to prove their skills. The third world countries can benefit from non-commercial programs.

### Disadvantage

Often there are no commercial group that reacts to the project. Bugs are everywhere, and no one takes responsibilities. Reliablity is lower than proprietary ones.
