-- Finds the Fallout window
local wnd = wapi.FindWindow(nil, "FALLOUT II")

-- Finds the process ID
local result, pid = wapi.GetWindowThreadProcessId(wnd)

-- Opens the process
local proc = wapi.OpenProcess(nil, 0, pid)

-- Reads current experience
local status, result, bytes = wapi.ReadProcessMemory(proc, 0x00678724, 4)

print("Reading current experience...")
print("Status: " .. tostring(status))
print("Experience: " .. smtm.udatatointeger(result))
print("Bytes read: " .. bytes)
print()

if status then
    print("Writing current experience...")
    status = wapi.WriteProcessMemory(proc, 0x00678724, smtm.integertoudata(100), 4)
    print("Status: " .. tostring(status))
end