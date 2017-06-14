

#include <sys/user.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/syscall.h>

#include <sys/reg.h>

int		main(void)
{
	pid_t				child;
	unsigned long int	old;

	child = fork();
	if (child == 0)
	{
		char* const args[] = {NULL};
		//ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		execv("./lolz", args);
	}
	else
	{
		int						status;
		struct user_regs_struct	regs;

		old = 0;
		//wait(NULL);
		ptrace(PTRACE_SEIZE, child, 0, 0);
		//ptrace(PTRACE_ATTACH, child, 0, 0);
		//waitpid(child, &status, 0);
		//while (1)
		//{
			/*ptrace(PTRACE_GETREGS, child, NULL, &regs);
			if (regs.rax == SYS_write && old != regs.rip && regs.rip == 0x80)
				printf("rip : %llx, eax : %lld\n", regs.rip, regs.rax);
			old = regs.rip;
			ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
			waitpid(child, &status, 0);
			if (WIFEXITED(status))
				break ;*/
			long orig_rax;
			orig_rax = ptrace(PTRACE_PEEKUSER, child, 8 * ORIG_RAX, NULL);
        	printf("The child made a system call %ld\n", orig_rax);
        	ptrace(PTRACE_CONT, child, NULL, NULL);

        	orig_rax = ptrace(PTRACE_PEEKUSER, child, 8 * ORIG_RAX, NULL);
        	printf("The child made a system call %ld\n", orig_rax);
        	ptrace(PTRACE_CONT, child, NULL, NULL);
		//}
	}
	return (0);
}