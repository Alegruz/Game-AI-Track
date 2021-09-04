# Exercises

## 1.12 How do clustered systems differ from multiprocessor systems? What is required for two machines belonging to a cluster to cooperate to provide a highly available service?

Multiprocessors operate in a single-core CPU computer system, while clustered systems operate as a collection of computer systems.

Clustered system needs to continue a service even if one or more systems in the cluster fail. This is provided by increasing the level of redundancy in the system.

### Answer

Clustered systems are typically constructed by combining multiple computers into a single system to perform a computational task distributed across the cluster. Multiprocessor systems on the other hand could be a single physical entity comprising of multiple CPUs. A clustered system is less tightly coupled than a multiprocessor system. Clustered system communicate using messages, while processors in a multiprocessor system could communicate using shared memory. In order for two machines to provide a highly available service, the state on the two machines should be replicated and should be consistently updated. When one of the machines fail, the other could then take-over the functionality of the failed machine.

## 1.13 Consider a computing cluster consisting of two nodes running a database. Describe two ways in which the cluster software can manage access to the data on the disk. Discuss the benefits and disadvantages of each

1. Asymmetric. One machine runs the database while the other one is in hot-standby mode to monitor the active machine.
   * Benefit: Works rather as a single system, thus problems that arise in traditional clustered system. Running single application is available.
   * Disadvantages: Only single machine is running, so full capacity is lower than the number of total machines.
2. Symmetric. Both machines run the application and monitors each other
   * Benefit: More efficient as it uses all of the available hardware
   * Disadvantages: Requires more than one application be available to run

### Answer

Consider the following two alternatives: **asymmetric clustering** and **parallel clustering**. With asymmetric clustering, one host runs the database application with the other host simply monitoring it. If the server fails, the monitoring hose becomes the active server. This is appropriate for providing redundancy. However, it does not utilize the potential processing power of both hosts. With parallel clustering, the database application can run in parallel on both hosts. The difficulty implementing parallel clusters is providing some form of distributed locking mechanisms for files on the shared disk.

## 1.14 What is the purpose of interrupts? How does an interrupt differ from a trap? Can traps be generated intentionally by a user program? If so, for what purpose?

### Purpose

To let the controller inform the device driver that it has finished its operation.

### Trap

Trap is a software-generated interrupt caused either by an error or by a specific request from a user that an operating-system service be performed by executing a system call.

### Answer

An interrupt is a hardware-generated change-of-flow within the system. An interrupt handler is summoned to deal with the cause of the interrupt; control is then returned to the interrupt context and instruction. A trap is a software-generated interrupt. An interrupt can be used to signal the completion of an I/O to obviate the need for device polling. A trap can be used to call operating system routines or to catch arithmetic errors.

## 1.15 Explain how the Linux kernel variables HZ and jiffies can be used to determine the number of seconds the system has been running since it was booted

HZ specifies the frequency of timer interrupts. jiffies represents the number of timer interrupts that have occurred since the system was booted. So by dividing the jiffies by HZ results in the number of seconds the system has been running since it was booted.

## 1.16 Direct memory access is used for high-speed I/O devices in order to avoid increasing the CPU’s execution load

### a. How does the CPU interface with the device to coordinate the transfer?

The device controller transfers an entire block of data directly to or from the device and main memory, with no intervention by the CPU.

### b. How does the CPU know when the memory operations are complete?

Only one interrupt is generated per block, to tell the device driver that the operation has completed, rather than the one interrupt per byte generated for low-speed devices.

### c. The CPU is allowed to execute other programs while the DMA controller is transferring data. Does this process interfere with the execution of the user programs? If so, describe what forms of interference are caused

Multiple components compete for cycles on a shared bus.

### Answer

The CPU can initiate a DMA operation by writing values into special registers that can be independently accessed by the device. The device initiates the corresponding operation once it receives a command from the CPU. When the device is finished with its operation, it interrupts the CPU to indicated the completion of the operation.

Both the device and the CPU can be accessing memory simultaneously. The memory controller provides access to the memory bus in a fair manner to these two entities. A CPU might therefore be unable to issue memory operations at peak speeds since it has to compete with the device in order to obtain access to the memory bus.

## 1.17 Some computer systems do not provide a privileged mode of operation in hardware. Is it possible to construct a secure operating system for these computer systems? Give arguments both that it is and that it is not possible

### Constructing a secure operationg system that do not provide a privileged mode of operation in hardware is possible

By restricting the accessibility of security to kernel mode, in other words, restricting the functionalities of the user to never interfere with the kernel mode, we can provide security.

### Constructing a secure operationg system that do not provide a privileged mode of operation in hardware is not possible

Operating system must be user friendly, thus systems without privileged mode of operations will greatly restrict the user's capabilities of communicating with other devices, especially I/O devices.

### Answer

An operating system for a machine of this type would need to remain in control (or monitor mode) at all times. This could be accomplished by two methods.

a. Software interpreation of all user programs (like some BASIC, Java, and LISP systems, for example). The software interpreter would provide, in software, what the hardware does not provide.

b. Require meant that all programs be written in high-level languages so that all object code is compiler-produced. The compiler would generate (either in-line or by function calls) the protection checks that the hardware is missing.

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

### Answer

In a single-processor systems, the memory needs to be updated when a processor issues updates to cached values. These updates can be performed immediately or in a lazy manner. In a multiprocessor system, different processors might be caching the same memory location in its local caches. When updates are made, the other cached locations need to be invalidated or updated. In distributed systems, consistency of cached memory values is not an issues. However, consistency problems might arise when a client caches file data.

## 1.22 Describe a mechanism for enforcing memory protection in order to prevent a program from modifying the memory associated with other programs

Operating system should know which memories are being used, and who are using them. When some program tries to modify a memory owned by another program, then the operating should either produce a trap or ignore the command.

### Answer

The processor could keep track of what locations are associated with each process and limit access to locations that are outside of a program's extent. Information regarding the extent of a program's memory could be maintained by using base and limits registers and by performing a check for every memory access.

## 1.23 Which network configuration—LAN or WAN—would best suit the following environments?

### a. A campus student union

LAN

### b. Several campus locations across a statewide university system

WAN

### c. A neighborhood

LAN

### Answer

a. A campus student union - A LAN.
b. Several campus locations across a statewide university system - A LAN, possible a WAN for very large campuses
c. A neighborhood - A LAN, possible a WAN for very large neighborhoods.

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
