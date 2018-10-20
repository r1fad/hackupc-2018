import psutil

proc_names = ["Atom", "Sublime", "Slack", "Google Chrome", "Spotify", "idea"]
process_info = []

for proc in  psutil.process_iter():
    # print(proc.as_dict(attrs=['pid','name','create_time','cpu_times']))
    # proc_name = proc.name()
    # condition = not proc_name.islower() and not proc_name.isupper() and '.' not in proc_name and ' ' in proc_name
    # if condition:
    #     print (proc_name)
    try:
        proc_name = proc.name()
        if proc_name in proc_names:
            proc_details = proc.as_dict(attrs=['pid','name','create_time','cpu_times'])
            proc_info = {}
            proc_info["name"] = proc_details["name"]
            proc_info["pid"] = proc_details["pid"]
            proc_info["start_time"] = proc_details["create_time"]
            proc_info["elapsed_time"] = proc_details["cpu_times"].user + proc_details["cpu_times"].system
            process_info.append(proc_info)
    except Exception:
        continue
print (process_info)
